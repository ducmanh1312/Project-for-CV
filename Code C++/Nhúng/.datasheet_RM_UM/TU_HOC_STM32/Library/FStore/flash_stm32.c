#if defined (STM32F10X_MD)
  #include "stm32f10x_conf.h"
#endif

#if defined (STM32F0XX)
  #include "stm32f0xx_conf.h"
#endif

#include "flash.h"

/***************************************************************/
bool Flash_ErasePage(uint32_t page_addr) {
  return (FLASH_ErasePage(page_addr) == FLASH_COMPLETE);
}

bool Flash_ProgramWord(uint32_t addr, uint32_t data) {
  return (FLASH_ProgramWord(addr, data) == FLASH_COMPLETE);
}

uint32_t Flash_ReadWord(const uint32_t addr) {
  return (*(__IO uint32_t*) addr);
}

/***************************************************************/
#if defined (STM32F10X_MD)     ////////////////// STM32F103 ////////////////////

#define FLASH_BANK2_BEGIN_ADDRESS   ((uint32_t)0x8080000)  // (stm32f10x_flash.c)

void Flash_Unlock(uint32_t addr)
{
  if (addr < FLASH_BANK2_BEGIN_ADDRESS)
  {
    FLASH_UnlockBank1();
  }
  else
  {
    #if defined (STM32F10X_XL)
      FLASH_UnlockBank2();  // stm32f10x_flash.h
    #endif
  }
}

void Flash_Lock(uint32_t addr)
{
  if (addr < FLASH_BANK2_BEGIN_ADDRESS)
  {
    FLASH_LockBank1();
  }
  else
  {
    #if defined (STM32F10X_XL)
      FLASH_LockBank2();  // stm32f10x_flash.h
    #endif
  }
}

#endif


#if defined (STM32F0XX)   ////////////////// STM32F030 ////////////////////
void Flash_Unlock(uint32_t addr) {
  FLASH_Unlock();
}

void Flash_Lock(uint32_t addr) {
  FLASH_Lock();
}
#endif

/***************************************************************/
