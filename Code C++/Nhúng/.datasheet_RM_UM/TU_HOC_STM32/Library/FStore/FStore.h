#ifndef __FSTORE_H
#define __FSTORE_H

#include "basic.h"
C_DECLS_BEGIN

/*************************************************************/
//#define  FSTORE_DEBUG

#define  PAGE_MARGIN     3
#define  KEY_COUNT       250

#define  PAGE_SIZE       1024       // stm32F103C8, stm32F030
#define  BLOCK_SIZE      4          // mỗi BLOCK = 4 byte
#define  BLOCK_PER_PAGE  (PAGE_SIZE / BLOCK_SIZE)
#define  BLOCK_DEFAULT   0xFFFFFFFF

/*************************************************************/
typedef struct
{
  uint32_t start_addr;
  uint32_t block_count;
  uint8_t  crc_base;

  uint32_t head_index;
  int      block_remain;
} FStore;

/***************************************************************/
bool FStore_Begin(FStore* fs, uint32_t start_addr, int page_count, uint8_t fs_id);
int  FStore_GetKey(FStore* fs, uint8_t key);
bool FStore_SetKey(FStore* fs, uint8_t key, uint16_t value);

int  FStore_GetKey8(FStore* fs, uint16_t key8);
bool FStore_SetKey8(FStore* fs, uint16_t key8, uint8_t value8);

void FStore_PrintInfo(FStore* fs);
int  FStore_CountBadBlock(FStore* fs);
int  FStore_CountDefaultBlock(FStore* fs);
int  FStore_CountPageErase(FStore* fs);

int  FStore_CountKeyUsed(FStore* fs);

bool FStore_SaveStruct(FStore* fs, void *my_struct, int len, int offset);
void FStore_ReadStruct(FStore* fs, void *my_struct, int len, int offset, const void *default_struct);

/***************************************************************/
C_DECLS_END
#endif /* __FSTORE_H */
