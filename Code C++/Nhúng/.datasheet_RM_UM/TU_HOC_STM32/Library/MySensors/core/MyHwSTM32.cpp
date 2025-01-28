
#include "MySensors.h"   // chỉnh sửa để có #define MY_GATEWAY_FEATURE
#include "MySensorsCore.h"  // MY_SLEEP_NOT_POSSIBLE
#include "MyHwSTM32.h"

#include "MyCustoms.h"  // chỉnh sửa


/********************************************************************************/
void hwReadConfigBlock(void* buf, void* adr, size_t length) {
	uint8_t* dst = static_cast<uint8_t*>(buf);
	int offs = reinterpret_cast<int>(adr);
	while (length-- > 0) {
		*dst++ = hwReadByte(offs++);
	}
}

void hwWriteConfigBlock(void* buf, void* adr, size_t length) {
	uint8_t* src = static_cast<uint8_t*>(buf);
	int offs = reinterpret_cast<int>(adr);
	while (length-- > 0) {
		hwWriteByte(offs++, *src++);
	}
}

uint8_t hwReadConfig(int adr) {
	uint8_t value;
	hwReadConfigBlock(&value, reinterpret_cast<void*>(adr), 1);
	return value;
}

void hwWriteConfig(int adr, uint8_t value) {
	uint8_t curr = hwReadConfig(adr);
	if (curr != value) {
		hwWriteConfigBlock(&value, reinterpret_cast<void*>(adr), 1);
	}
}


/********************************************************************************/
void hwWriteByte(unsigned int offset, uint8_t data) {
  customWriteByte(offset, data);
}

uint8_t hwReadByte(unsigned int offset) {
  return customReadByte(offset);
}


/********************************************************************************/
void hwInit()
{
//  #if defined(MY_GATEWAY_SERIAL)
//    while (!MY_SERIALDEVICE) {}
//  #endif

  customInit();
}

/********************************************************************************/
void hwWatchdogReset() {
  customWatchdogReset();
}

void hwReboot() {
	NVIC_SystemReset();
	while (true);
}

//int8_t hwSleep(unsigned long ms) {
//	// TODO: Not supported!
//	(void)ms;
//	return MY_SLEEP_NOT_POSSIBLE;
//}
//
//int8_t hwSleep(uint8_t interrupt, uint8_t mode, unsigned long ms) {
//	// TODO: Not supported!
//	(void)interrupt;
//	(void)mode;
//	(void)ms;
//	return MY_SLEEP_NOT_POSSIBLE;
//}
//
//int8_t hwSleep(uint8_t interrupt1, uint8_t mode1, uint8_t interrupt2, uint8_t mode2,
//               unsigned long ms)
//{
//	// TODO: Not supported!
//	(void)interrupt1;
//	(void)mode1;
//	(void)interrupt2;
//	(void)mode2;
//	(void)ms;
//	return MY_SLEEP_NOT_POSSIBLE;
//}


#if defined(MY_DEBUG) || defined(MY_SPECIAL_DEBUG)
  uint16_t hwCPUVoltage() {
    // TODO: Not supported!
    return 0;
  }

  uint16_t hwCPUFrequency() {
    // TODO: Not supported!
    return 0;
  }

  uint16_t hwFreeMem() {
    // TODO: Not supported!
    return 0;
  }
#endif


#ifdef MY_DEBUG
  #include <stdarg.h>
  #include <stdio.h>

  void hwDebugPrint(const char *fmt, ... ) {
    char fmtBuffer[MY_SERIAL_OUTPUT_SIZE];
  #ifdef MY_GATEWAY_FEATURE
    // prepend debug message to be handled correctly by controller (C_INTERNAL, I_LOG_MESSAGE)
    snprintf_P(fmtBuffer, sizeof(fmtBuffer), PSTR("0;255;%d;0;%d;"), C_INTERNAL, I_LOG_MESSAGE);
//    MY_SERIALDEVICE.print(fmtBuffer);
    printf("%s", fmtBuffer);
  #else
    // prepend timestamp (AVR nodes)
  //	MY_SERIALDEVICE.print(hwMillis());
  //MY_SERIALDEVICE.print(" ");
    printf("%d  ", hwMillis());

  #endif
    va_list args;
    va_start (args, fmt );

  #ifdef MY_GATEWAY_FEATURE
    // Truncate message if this is gateway node
    //vsnprintf_P(fmtBuffer, sizeof(fmtBuffer), fmt, args);
    vsnprintf(fmtBuffer, sizeof(fmtBuffer), fmt, args);
    fmtBuffer[sizeof(fmtBuffer) - 2] = '\n';
    fmtBuffer[sizeof(fmtBuffer) - 1] = '\0';
  #else
    //vsnprintf_P(fmtBuffer, sizeof(fmtBuffer), fmt, args);
    vsnprintf(fmtBuffer, sizeof(fmtBuffer), fmt, args);
  #endif

    va_end (args);
  //	MY_SERIALDEVICE.print(fmtBuffer);
    printf("%s", fmtBuffer);
    //MY_SERIALDEVICE.flush();
    //MY_SERIALDEVICE.write(freeRam());
  }
#endif

