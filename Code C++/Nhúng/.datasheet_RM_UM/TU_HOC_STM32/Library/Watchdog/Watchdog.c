
#include "basic.h"
#include "Watchdog.h"

/**********************************************************************/
#ifdef STM32F10X_MD
  bool Watchdog_hardware_begin() {
    uint16_t opt_byte_user = OB->USER;
    if (BITMASK_IS_CLEAR(opt_byte_user, OB_IWDG_SW))
      return true;

    FLASH_Unlock();

    BITMASK_CLEAR(opt_byte_user, OB_IWDG_SW);
    if (FLASH_ProgramOptionByteData((uint32_t)(&OB->USER), opt_byte_user) != FLASH_COMPLETE) {
      FLASH_EraseOptionBytes();
      FLASH_ProgramOptionByteData((uint32_t)(&OB->USER), opt_byte_user);   // try again
    }

    FLASH_Lock();

    opt_byte_user = OB->USER;              // check again
    if (BITMASK_IS_CLEAR(opt_byte_user, OB_IWDG_SW))
      return true;

    return false;
  }

  void Watchdog_hardware_end() {
    uint16_t opt_byte_user = OB->USER;
    if (BITMASK_IS_SET(opt_byte_user, OB_IWDG_SW))
      return;

    FLASH_Unlock();
    FLASH_EraseOptionBytes();
    FLASH_Lock();
  }
#endif


/**********************************************************************/
#ifdef STM32F0XX
  bool Watchdog_hardware_begin() {
    uint16_t opt_byte_user = OB->USER;
    if (BITMASK_IS_CLEAR(opt_byte_user, OB_IWDG_SW))
      return true;

    FLASH_Unlock();
    FLASH_OB_Unlock();

    BITMASK_CLEAR(opt_byte_user, OB_IWDG_SW);
    if (FLASH_OB_WriteUser(opt_byte_user) != FLASH_COMPLETE) {
      FLASH_OB_Erase();
      FLASH_OB_WriteUser(opt_byte_user);   // try again
    }

    FLASH_OB_Lock();
    FLASH_Lock();

    opt_byte_user = OB->USER;  // check again
    if (BITMASK_IS_CLEAR(opt_byte_user, OB_IWDG_SW))
      return true;

    return false;
  }

  void Watchdog_hardware_end() {
    uint16_t opt_byte_user = OB->USER;
    if (BITMASK_IS_SET(opt_byte_user, OB_IWDG_SW))
      return;

    FLASH_Unlock();
    FLASH_OB_Unlock();

    FLASH_OB_Erase();

    FLASH_OB_Lock();
    FLASH_Lock();
  }
#endif


/**********************************************************************/
#define KR_KEY_RELOAD    ((uint16_t)0xAAAA)
#define KR_KEY_ENABLE    ((uint16_t)0xCCCC)

/**********************************************************************/
void Watchdog_begin(int ms) {
  IWDG->KR = IWDG_WriteAccess_Enable;  // Enable write access to IWDG_PR and IWDG_RLR

  IWDG->PR  = IWDG_Prescaler_64;
  IWDG->RLR = ms / 1.6;

  Watchdog_reset();          // reload IWDG counter
  IWDG->KR = KR_KEY_ENABLE;  // enable IWDG (the LSI oscillator will be enabled by hardware)
}

/**********************************************************************/
void Watchdog_reset() {
  IWDG->KR = KR_KEY_RELOAD;
}

/**********************************************************************/
void Watchdog_setPrescaler(uint8_t prescaler) {
  IWDG->KR = IWDG_WriteAccess_Enable;  // Enable write access to IWDG_PR and IWDG_RLR
  IWDG->PR = prescaler;
}

/**********************************************************************/

/*==============================================================================

Change log

190127 - TranDucNam
  Update: thêm hàm
    void Watchdog_hardware_end();
    Disable chức năng Watchdog hardware

==============================================================================*/

