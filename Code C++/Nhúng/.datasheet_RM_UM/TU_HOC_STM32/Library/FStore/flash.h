#ifndef __FLASH_H
#define __FLASH_H

#include "basic.h"

C_DECLS_BEGIN

/*************************************************************/
#include <stdint.h>
#include <stdbool.h>

/*************************************************************/
void     Flash_Unlock(uint32_t addr);
void     Flash_Lock(uint32_t addr);

bool     Flash_ErasePage(uint32_t page_addr);
bool     Flash_ProgramWord(uint32_t addr, uint32_t data);
uint32_t Flash_ReadWord(uint32_t addr);

/*************************************************************/
C_DECLS_END
#endif /* __FLASH_H */
