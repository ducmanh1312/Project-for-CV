#ifndef MyHwSTM32_h
#define MyHwSTM32_h

#include "Core.h"
#include "MyHw.h"

#include <stdio.h>                                                // chỉnh sửa
#define snprintf_P(s, f, ...)   snprintf((s), (f), __VA_ARGS__)   // chỉnh sửa

// Define these as macros to save valuable space
//#define hwDigitalWrite(__pin, __value)  digitalWrite(__pin, __value)
//#define hwDigitalRead(__pin)            digitalRead(__pin)
//#define hwPinMode(__pin, __value)       pinMode(__pin, __value)
  #define hwMillis()                      millis()
//#define hwRandomNumberInit()            randomSeed(analogRead(MY_SIGNING_SOFT_RANDOMSEED_PIN))


void    hwInit();
void    hwWatchdogReset();
void    hwReboot();

void    hwWriteByte(unsigned int offset, uint8_t data);
uint8_t hwReadByte(unsigned int offset);

void    hwReadConfigBlock( void* buf, void* adr, size_t length);
void    hwWriteConfigBlock(void* buf, void* adr, size_t length);
uint8_t hwReadConfig( int adr);
void    hwWriteConfig(int adr, uint8_t value);


/**
 * Disable all interrupts.
 * Helper function for MY_CRITICAL_SECTION.
 */
static __inline__ uint8_t __disableIntsRetVal(void)
{
	__disable_irq();
	return 1;
}

/**
 * Restore priority mask register.
 * Helper function for MY_CRITICAL_SECTION.
 */
static __inline__ void __priMaskRestore(const uint32_t *priMask)
{
	__set_PRIMASK(*priMask);
}

#ifndef DOXYGEN
  #define MY_CRITICAL_SECTION    for ( uint32_t __savePriMask __attribute__((__cleanup__(__priMaskRestore))) = __get_PRIMASK(), __ToDo = __disableIntsRetVal(); __ToDo ; __ToDo = 0 )
#endif  /* DOXYGEN */

#endif // MyHwSTM32_h
