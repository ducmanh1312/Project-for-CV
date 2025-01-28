
#include "random.h"
#include "ADC.h"

/**********************************************************************/
#if defined (STM32F10X_MD)
	void     Rand_begin()  {}
	uint8_t  Rand_get8()   {}
	uint16_t Rand_get12()  {}
	uint16_t Rand_get16()  {}
	uint32_t Rand_get32()  {}
#endif
/**********************************************************************/


/**********************************************************************/
#if defined (STM32F0XX)
  void Rand_begin(uint32_t seed) {
		BITMASK_SET(RCC->AHBENR, RCC_AHBPeriph_CRC);  // Enable CRC AHB clock interface
		CRC_DeInit();               // DeInit CRC peripheral
		CRC_SetInitRegister(seed);  // Init the INIT register

		ADC1_begin();
		ADC->CCR |= ADC_CCR_TSEN | ADC_CCR_VREFEN;  /// enable Temperature & VREF
  }

  uint32_t Rand_get32() {
	  uint32_t rand = CRC->DR;                                   // get the current value
		CRC->DR = ADC1_read_TempSensor(ADC_SampleTime_1_5Cycles);  // compute the next value
    return rand;
  }

  uint16_t Rand_get16() {
    return Rand_get32();
  }

  uint16_t Rand_get12() {
    return Rand_get32() & 0xFFF;
  }

  uint8_t Random_read8() {
    return Rand_get32();
  }
#endif

/**********************************************************************/
