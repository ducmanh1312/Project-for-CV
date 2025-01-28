#include "FStore.h"
#include "flash.h"
#include "crc8.h"
#include <stdio.h>

#define  KEY_ERASE_COUNT  (KEY_COUNT - 1)

#define  POS_VALUE   0
#define  POS_KEY    16
#define  POS_CRC    24

#define  BLOCK_CREATE(key, value, crc)  ( ((key) << POS_KEY) | ((value) << POS_VALUE) | ((crc) << POS_CRC) )
#define  BLOCK_GET_KEY(block)           ( ((block) >> POS_KEY  ) &   0xFF )
#define  BLOCK_GET_VALUE(block)         ( ((block) >> POS_VALUE) & 0xFFFF )
#define  BLOCK_GET_CRC(block)           ( ((block) >> POS_CRC  ) &   0xFF )

#define  BLOCK_IS_GOOD(block)           ( BLOCK_GET_CRC(block) == 0x00 )
#define  BLOCK_IS_DEFAULT(block)        ( (block) == BLOCK_DEFAULT )
#define  INDEX_IS_DEFAULT(index)        ( BLOCK_IS_DEFAULT( Block_ReadBlock(fs, index) ))

#define  PAGE(block)    ( (block) / BLOCK_PER_PAGE )
#define  ADDR(fs, idx)  ( (fs)->start_addr + (idx)*BLOCK_SIZE )

#define  WRAP_UPPER(x, wrap)  ( (((int)(x)) < (wrap)) ? (x) : ((x) - (wrap)) )
#define  WRAP_LOWER(x, wrap)  ( (((int)(x)) < 0     ) ? ((x) + (wrap)) : (x) )

#define  BYTE(x)  ( (x) & 0xFF )

/***************************************************************/
#if defined  (FSTORE_DEBUG)
  #define  FStore_DebugMsg  printf
#else
  void FStore_DebugMsg() {;}
#endif

/***************************************************************/
uint32_t Block_ReadBlock(FStore* fs, uint32_t idx);
uint32_t Block_ReadBlockCRC(FStore* fs, uint32_t idx);
bool     Block_PushBlock(FStore* fs, uint8_t key, uint16_t value);
uint32_t Block_UpdateCRC(FStore* fs, uint32_t idx, uint32_t block);

void FStore_FindHeadIndex(FStore* fs);
int  FStore_GetKeyIndex(FStore* fs, uint8_t key);
int  FStore_CountAvailableBlock(FStore* fs);
bool FStore_Check_Copy_Erase(FStore* fs);

/***************************************************************/
uint32_t Block_UpdateCRC(FStore* fs, uint32_t idx, uint32_t block)
{
  uint8_t crc = fs->crc_base;
  CRC8_UPDATE(crc, BYTE(idx >> 8));
  CRC8_UPDATE(crc, BYTE(idx >> 0));
  CRC8_UPDATE(crc, BLOCK_GET_KEY(block));
  CRC8_UPDATE(crc, BLOCK_GET_VALUE(block) >> 8);
  CRC8_UPDATE(crc, BLOCK_GET_VALUE(block) >> 0);
  return (block ^ BLOCK_CREATE(0, 0, crc));
}

/***************************************************************/
uint32_t inline Block_ReadBlock(FStore* fs, uint32_t idx)
{
  return Flash_ReadWord(ADDR(fs, idx));
}

/***************************************************************/
uint32_t inline Block_ReadBlockCRC(FStore* fs, uint32_t idx)
{
  uint32_t read_block = Block_ReadBlock(fs, idx);
  if (read_block == BLOCK_DEFAULT)
    return BLOCK_DEFAULT;
  return Block_UpdateCRC(fs, idx, read_block);
}

/***************************************************************/
bool Block_PushBlock(FStore* fs, uint8_t key, uint16_t value)
{
  int wrap  = fs->block_count;
  int start = fs->head_index;
  for (int i = start - wrap; i < start; i++)
  {
    uint32_t idx = WRAP_LOWER(i, wrap);
    if ( ! INDEX_IS_DEFAULT(idx))
      continue;

    fs->head_index = WRAP_LOWER(i + 1, wrap);

    uint32_t push_block = BLOCK_CREATE(key, value, 0);
    push_block = Block_UpdateCRC(fs, idx, push_block);

    uint32_t push_addr = ADDR(fs, idx);
    Flash_ProgramWord(push_addr, push_block);
    return (push_block == Flash_ReadWord(push_addr));
  }

  FStore_DebugMsg("[ERR] Block_PushBlock: out of DEFAULT BLOCKs\n");
  return false;
}

/***************************************************************/
void FStore_FindHeadIndex(FStore* fs)
{
  fs->head_index = 0;         // default value for empty flash
  int wrap = fs->block_count;
  for (int block_begin = 0; block_begin < wrap; block_begin += BLOCK_PER_PAGE)
  {
    if (INDEX_IS_DEFAULT(block_begin))
      continue;

    int start = block_begin + BLOCK_PER_PAGE - 1;
    for (int block_end = start - wrap; block_end < start; block_end += BLOCK_PER_PAGE)
    {
      if ( ! INDEX_IS_DEFAULT(WRAP_LOWER(block_end, wrap)) )
        continue;

      int start = WRAP_LOWER(block_end + 1 - BLOCK_PER_PAGE, wrap);
      for (int idx = start; idx < start + BLOCK_PER_PAGE; idx++)
      {
        if ( ! INDEX_IS_DEFAULT(idx))
          continue;

        fs->head_index = idx;
        return;
      }
    }
  }
}

/***************************************************************/
bool FStore_Begin(FStore* fs, uint32_t start_addr, int page_count, uint8_t fs_id)
{
  if ( (start_addr % PAGE_SIZE) != 0 )
  {
    FStore_DebugMsg("[ERR] FStore_Begin: illegal, start_addr = 0x%X\n", start_addr);
    return false;
  }

  uint8_t crc = fs_id;      // init value
  CRC8_UPDATE(crc, BYTE(start_addr >> 24));
  CRC8_UPDATE(crc, BYTE(start_addr >> 16));
  CRC8_UPDATE(crc, BYTE(start_addr >>  8));
  CRC8_UPDATE(crc, page_count);
  fs->crc_base = crc;

  fs->start_addr  = start_addr;
  fs->block_count = page_count * BLOCK_PER_PAGE;

  FStore_FindHeadIndex(fs);

  fs->block_remain = 0;
  if ( ! FStore_Check_Copy_Erase(fs) )
  {
    Flash_Lock(fs->start_addr);
    return false;
  }

  if (FStore_GetKey(fs, KEY_ERASE_COUNT) == BLOCK_DEFAULT)  // init erase counter
    FStore_SetKey(fs, KEY_ERASE_COUNT, 0);

  return true;
}

/***************************************************************/
int FStore_GetKey(FStore* fs, uint8_t key)
{
  int wrap  = fs->block_count;
  int start = fs->head_index - 1;
  int limit = fs->head_index;
  for (int i = start; i >= limit - wrap; i--)
  {
    uint32_t idx = WRAP_LOWER(i, wrap);
    uint32_t block = Block_ReadBlockCRC(fs, idx);

    if ( (BLOCK_GET_KEY(block) == key) && BLOCK_IS_GOOD(block) )
      return BLOCK_GET_VALUE(block);

    if (BLOCK_IS_DEFAULT(block))
      return BLOCK_DEFAULT;
  }
  return BLOCK_DEFAULT;
}

/***************************************************************/
int FStore_GetKey8(FStore* fs, uint16_t key8)
{
  uint8_t key16 = key8 >> 1;   // = key 8 / 2
  int data16 = FStore_GetKey(fs, key16);

  return (key8 & 1) ? BYTE(data16 >> 0) : BYTE(data16 >> 8);
}


/***************************************************************/
bool FStore_SetKey8(FStore* fs, uint16_t key8, uint8_t value8)
{
  uint8_t key16 = key8 >> 1;   // = key 8 / 2
  int value16 = FStore_GetKey(fs, key16);

  if (key8 & 1)
    value16 = (value16 & 0xFF00) | (value8 << 0);
  else
    value16 = (value16 & 0x00FF) | (value8 << 8);

  return FStore_SetKey(fs, key16, value16);
}

/***************************************************************/
int FStore_GetKeyIndex(FStore* fs, uint8_t key)
{
  int wrap  = fs->block_count;
  int start = fs->head_index - 1;
  int limit = fs->head_index;
  for (int i = start; i >= limit - wrap; i--)
  {
    uint32_t idx = WRAP_LOWER(i, wrap);
    uint32_t block = Block_ReadBlockCRC(fs, idx);
    if ( (BLOCK_GET_KEY(block) == key) && BLOCK_IS_GOOD(block) )
      return idx;
  }
  return -1;
}

/***************************************************************/
bool FStore_SetKey(FStore* fs, uint8_t key, uint16_t value)
{
  if (key >= KEY_COUNT)
  {
    FStore_DebugMsg("[ERR] FStore_SetKey: invalid key, %d %d\n", key, KEY_COUNT);
    return false;
  }

  if (FStore_GetKey(fs, key) == value)
    return true;

  Flash_Unlock(fs->start_addr);
  if ( ! Block_PushBlock(fs, key, value) )
  {
    Flash_Lock(fs->start_addr);
    return false;
  }
  Flash_Lock(fs->start_addr);
  fs->block_remain--;

  if ( ! FStore_Check_Copy_Erase(fs) )
  {
    Flash_Lock(fs->start_addr);
    return false;
  }

  return true;
}

/***************************************************************/
int FStore_CountBadBlock(FStore* fs)
{
  int block_count = fs->block_count;
  int bad_block = 0;
  for (int idx = 0; idx < block_count; idx++)
  {
    uint32_t block = Block_ReadBlockCRC(fs, idx);
    if ( ! (BLOCK_IS_DEFAULT(block) || BLOCK_IS_GOOD(block)) )
      bad_block++;
  }
  return bad_block;
}

/***************************************************************/
int  FStore_CountDefaultBlock(FStore* fs)
{
  int block_count = fs->block_count;
  int default_block = 0;
  for (int idx = 0; idx < block_count; idx++)
  {
    if (INDEX_IS_DEFAULT(idx))
      default_block++;
  }
  return default_block;
}

/***************************************************************/
int FStore_CountKeyUsed(FStore* fs)
{
  int key_used = 0;

  for (int key = 0; key < KEY_COUNT; key++) {
    if (FStore_GetKey(fs, key) != BLOCK_DEFAULT)
      key_used++;
  }

  return key_used;
}


/***************************************************************/
int FStore_CountAvailableBlock(FStore* fs)
{
  int wrap  = fs->block_count;
  int start = fs->head_index - wrap;
  int limit = start + BLOCK_PER_PAGE; // check up to BLOCK_PER_PAGE next blocks
  int num_available = 0;
  for (int i = start; i < limit; i++)
  {
    if (INDEX_IS_DEFAULT( WRAP_LOWER(i, wrap) ))
      num_available++;
  }
  return num_available;
}


/***************************************************************/
uint8_t inline check_and_set_key_pos(FStore* fs, uint8_t* key_pos, uint32_t idx, uint8_t pos)
{
  uint32_t block = Block_ReadBlockCRC(fs, idx);
  uint8_t key = BLOCK_GET_KEY(block);
  if ( BLOCK_IS_GOOD(block) && (key < KEY_COUNT) )
    key_pos[key] = pos;
  return key;
}


/***************************************************************/
bool FStore_Check_Copy_Erase(FStore* fs)
{
  if (fs->block_remain > PAGE_MARGIN)
    return true;

  int block_available = FStore_CountAvailableBlock(fs);

  // Check - update block_copied
  uint8_t key_pos[KEY_COUNT];       // BYTE array
  const uint8_t DO_NOT_COPY = 0xFF;
  for (int i = 0; i < KEY_COUNT; i++)
    key_pos[i] = DO_NOT_COPY;       // init array

  int wrap = fs->block_count;
  int erased_page_begin = BLOCK_PER_PAGE * (1 + PAGE(fs->head_index + block_available - 1));
  erased_page_begin = WRAP_UPPER(erased_page_begin, wrap);

  // 1: page sẽ bị xóa
  for (int pos = 0; pos < BLOCK_PER_PAGE-1; pos++)
    check_and_set_key_pos(fs, key_pos, erased_page_begin + pos, BYTE(pos));

  uint8_t FF_key = check_and_set_key_pos(fs, key_pos, erased_page_begin + (BLOCK_PER_PAGE-1), 0x00);

  // 2: Các page còn lại: Clear pos
  int start = erased_page_begin + BLOCK_PER_PAGE;
  int limit = erased_page_begin;
  for (int i = start - wrap; i < limit; i++)
    check_and_set_key_pos(fs, key_pos, WRAP_LOWER(i, wrap), DO_NOT_COPY);

  //============================================================//
  // 3: count
  int block_copied = 0;
  for (int key = 0; key < KEY_COUNT; key++)
  {
    if (key_pos[key] != DO_NOT_COPY)
      block_copied++;
  }

  // 4: check again
  fs->block_remain = block_available - block_copied;
  if (fs->block_remain > PAGE_MARGIN)
    return true;

  if (fs->block_remain < 0)
  {
    FStore_DebugMsg("\t[ERR] Flash_check: not enough: %d %d\n", block_available, block_copied);
    return false;
  }

  // Copy
  Flash_Unlock(fs->start_addr);

  #define  KEY2VAL(key)  BLOCK_GET_VALUE( Block_ReadBlock(fs, erased_page_begin + key_pos[key]) )
  #define  TRY_PUSH_BLOCK(key, value)  { if (!Block_PushBlock(fs, key, value)) return false; }

  if (key_pos[KEY_ERASE_COUNT] != DO_NOT_COPY)
    TRY_PUSH_BLOCK(KEY_ERASE_COUNT, 1 + KEY2VAL(KEY_ERASE_COUNT));   // increment Erase Count

  if (key_pos[FF_key] != DO_NOT_COPY)
  {
    key_pos[FF_key] = DO_NOT_COPY;
    TRY_PUSH_BLOCK(FF_key, KEY2VAL(FF_key));
  }

  for (int key = 0; key < KEY_ERASE_COUNT; key++)
  {
    if (key_pos[key] != DO_NOT_COPY)
      TRY_PUSH_BLOCK(key, KEY2VAL(key));
  }

  // Erase
  if ( ! Flash_ErasePage(ADDR(fs, erased_page_begin)) )
  {
    FStore_DebugMsg("  [ERR] Flash_check: Erase failed\n");
    return false;
  }
  fs->block_remain = 0;       // force next FStore_Check_Copy_Erase()

  Flash_Lock(fs->start_addr);
  return true;
}

/***************************************************************/
void FStore_PrintInfo(FStore* fs)
{
  printf("  start addr   = %08X\n", fs->start_addr);
  printf("  page count   = %8d\n", PAGE(fs->block_count));
  printf("\n");
  printf("  head index   = %8d\n", fs->head_index);
  printf("  block remain = %8d\n", fs->block_remain);
  printf("\n");
  printf("  erase count  = %8d\n", FStore_CountPageErase(fs));
  printf("  bad block    = %8d\n", FStore_CountBadBlock(fs));
  printf("\n");
}

/***************************************************************/
int  FStore_CountPageErase(FStore* fs)
{
  int page_count = PAGE(fs->block_count);

  int erase_index = FStore_GetKeyIndex(fs, KEY_ERASE_COUNT);
  int erase_value = BLOCK_GET_VALUE( Block_ReadBlock(fs, erase_index) );

  int page_delta = PAGE(fs->head_index) - PAGE(erase_index);
  page_delta = WRAP_LOWER(page_delta, page_count);

  int erase_count = page_delta + (erase_value - 1) * (page_count - 1);
  return (erase_count < 0) ? 0 : erase_count;
}

/***************************************************************/
bool FStore_SaveStruct(FStore* fs, void *my_struct, int len, int offset)
{
  uint16_t *my_struct16 = (uint16_t*)(my_struct);

  for (int i = 0; i < (len / 2); i++)
  {
    uint8_t key = offset + i;
    int data = my_struct16[i];
    if ( !FStore_SetKey(fs, key, data) )
      return false;
  }

  return true;
}

/***************************************************************/
void FStore_ReadStruct(FStore* fs, void *my_struct, int len, int offset, const void *default_struct)
{
  uint16_t *my_struct16      = (uint16_t*)(my_struct);
  uint16_t *default_struct16 = (uint16_t*)(default_struct);

  for (int i = 0; i < (len / 2); i++)
  {
    uint8_t key = offset + i;
    int data = FStore_GetKey(fs, key);
    my_struct16[i] = (data != BLOCK_DEFAULT) ? data : default_struct16[i];
    //printf("FStore_ReadStruct: %d  %d\n", i, (data != BLOCK_DEFAULT) ? 1 : 0);
  }
}

/***************************************************************/
