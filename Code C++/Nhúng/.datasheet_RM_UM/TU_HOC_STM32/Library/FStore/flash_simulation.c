/***************************************************************/
#include <stdio.h>
#include "flash.h"

/***************************************************************/
#define BLOCK_DEFAULT     ((uint32_t)0xFFFFFFFF)

#define PAGE_SIZE         (1024)
#define BLOCK_SIZE           (4) // chuyển đổi index thành addr (mỗi BLOCK = 4 byte)
#define BLOCK_PER_PAGE    (PAGE_SIZE / BLOCK_SIZE)

#define  SIMULATION_FLASH_SIZE     (BLOCK_PER_PAGE * 16)
uint32_t Flash[SIMULATION_FLASH_SIZE];

bool Flash_is_lock = true;

int erase_cnt = 0;

/***************************************************************/
void Flash_clear();
void Flash_save_text();
void Flash_load_text();

/***************************************************************/
void Flash_Unlock(uint32_t addr)
{
  Flash_is_lock = false;
}

/***************************************************************/
void Flash_Lock(uint32_t addr)
{
  Flash_is_lock = true;
}

/***************************************************************/
bool Flash_ErasePage(uint32_t page_addr)
{
  if (Flash_is_lock)
  {
    printf("[ERR] Flash_ErasePage: Flash_is_lock\n");
    return false;
  }

  page_addr /= BLOCK_SIZE;

  for (int i = 0; i < BLOCK_PER_PAGE; i++)
    Flash[page_addr + i] = BLOCK_DEFAULT;

  erase_cnt++;
  return true;
}

/***************************************************************/
bool Flash_ProgramWord(uint32_t addr, uint32_t data)
{
  if (Flash_is_lock)
  {
    printf("[ERR] Flash_ProgramWord: Flash_is_lock\n");
    return false;
  }

  addr /= BLOCK_SIZE;

  if (Flash[addr] != BLOCK_DEFAULT)
  {
    printf("[ERR] Flash_ProgramWord: overwrite, addr = %08X\n", addr);
    return false;
  }

  Flash[addr] = data;
  return true;
}

/***************************************************************/
uint32_t Flash_ReadWord(uint32_t addr)
{
  addr /= BLOCK_SIZE;
  return Flash[addr];
}


/*************************************************************/
void Flash_clear()
{
  for (int i = 0; i < SIMULATION_FLASH_SIZE; i++)
    Flash[i] = BLOCK_DEFAULT;
}

/*************************************************************/
void Flash_save_text()
{
  FILE *flash_txt = fopen("FLASH.txt", "w");
  for (int i = 0; i < SIMULATION_FLASH_SIZE; i++)
    fprintf(flash_txt, "%08X\n", Flash[i]);
  fclose(flash_txt);
}

/*************************************************************/
void Flash_load_text()
{
  #define LINE_LEN   10  // = (%08X + '\n' + NULL)
  char line[LINE_LEN];

  FILE *flash_txt = fopen("FLASH.txt", "r");
  for (int i = 0; i < SIMULATION_FLASH_SIZE; i++)
  {
    fgets(line, LINE_LEN, flash_txt);
    Flash[i] = (int)strtoul(line, NULL, 16);
  }
  fclose(flash_txt);
}

/***************************************************************/
