#include "ADC.h"


/**********************************************************************/
#if defined (STM32F10X_MD)

  void ADC1_begin() {
    RCC_ADCCLKConfig(RCC_PCLK2_Div8);                // ADCCLK = PCLK2 / div
    BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_ADC1);  // enable clock ADC1
    ADC_DeInit(ADC1);

    ADC1->CR1 = ADC_Mode_Independent;
    ADC1->CR2 = ADC_DataAlign_Left
              | ADC_ExternalTrigConv_None;
    ADC1->SQR1 = 0;  // NbrOfChannel = 1

    BITMASK_SET(ADC1->CR2, ADC_CR2_ADON);  // enable ADC1

    BITMASK_SET(ADC1->CR2, ADC_CR2_RSTCAL);     // reset calibration
    while ((ADC1->CR2 & ADC_CR2_RSTCAL) != 0);  // wait_process reset calibration
    BITMASK_SET(ADC1->CR2, ADC_CR2_CAL);        // start calibration
    while ((ADC1->CR2 & ADC_CR2_CAL) != 0);     // wait_process calibration complete

    BITMASK_SET(SCB->SCR, SCB_SCR_SEVONPEND_Msk);  // enable events
    BITMASK_SET(ADC1->CR1, ADC_CR1_EOCIE);         // Interrupt enable for EOC
  }

	void ADC1_temp_sensor_begin() {
		ADC1->CR2 |= ADC_CR2_TSVREFE;  // Temperature & VREF sensor enabled
	}

//#define ADC_CFG_SAMPLE_TIME_SMPR1(ch, time) (ADC1->SMPR1 = (ADC1->SMPR1 & ~(0b111 << (3*(ch)))) | ((time) << (3*(ch))))
//#define ADC_CFG_SAMPLE_TIME_SMPR2(ch, time) (ADC1->SMPR2 = (ADC1->SMPR2 & ~(0b111 << (3*(ch)))) | ((time) << (3*(ch))))
  #define ADC_CFG_SAMPLE_TIME(reg, ch, time)  (reg = (reg & ~(0b111 << (3*(ch)))) | ((time) << (3*(ch))))

  uint32_t ADC1_read16(int channel, int sample_time) {
    if (channel < 10)
      //ADC_CFG_SAMPLE_TIME_SMPR2(channel -  0, sample_time);
      ADC_CFG_SAMPLE_TIME(ADC1->SMPR2, channel, sample_time);
    else
      //ADC_CFG_SAMPLE_TIME_SMPR1(channel - 10, sample_time);
      ADC_CFG_SAMPLE_TIME(ADC1->SMPR1, channel - 10, sample_time);

    ADC1->SQR3 = channel;
    BITMASK_SET(ADC1->CR2, ADC_CR2_ADON);  // start conversion

    ADC1->SR = 0;  // clear EOC flag
    ADC1->SR;      // wait_process clear EOC flag
    NVIC_ClearPendingIRQ(ADC1_2_IRQn);
    do {__WFE();} while ((ADC1->SR & ADC_FLAG_EOC) == 0);  // Wait end of conversion

    return ADC1->DR;  // read data conversion
  }

#endif
/**********************************************************************/


/**********************************************************************/
#if defined (STM32F0XX)
  void ADC1_begin() {
    BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_ADC1);  // enable clock

    ADC_DeInit(ADC1);
    ADC1->CFGR1 = ADC_Resolution_12b
                | ADC_DataAlign_Left
                | ADC_ExternalTrigConvEdge_None
                | ADC_ScanDirection_Upward;
    ADC1->CFGR2 = ADC_ClockMode_SynClkDiv4;  // ADC clock = PCLK / 4

    ADC1->CR = ADC_CR_ADCAL;          // ADC Calibration
    while (ADC1->CR & ADC_CR_ADCAL);  // wait_process calibration complete

    ADC1->CR = ADC_CR_ADEN;                     // enable ADC1
    while ((ADC1->ISR & ADC_FLAG_ADRDY) == 0);  // wait_process ADC1 ready

    BITMASK_SET(SCB->SCR, SCB_SCR_SEVONPEND_Msk);  // enable events
    ADC1->IER = ADC_IER_EOCIE;  // End of conversion interrupt enable
  }

	void ADC1_temp_sensor_begin() {
		ADC->CCR |= ADC_CCR_TSEN | ADC_CCR_VREFEN;  // Temperature & VREF sensor enabled
	}

  uint32_t ADC1_read16(int channel, int sample_time)
  {
    ADC1->CHSELR = channel;
    ADC1->SMPR   = sample_time;
    ADC1->CR = ADC_CR_ADSTART;  // start conversion

    ADC1->ISR = ADC_FLAG_EOC;
    ADC1->ISR;
    NVIC_ClearPendingIRQ(ADC1_COMP_IRQn);
    do {__WFE();} while ((ADC1->ISR & ADC_FLAG_EOC) == 0);

    return ADC1->DR;
  }

#endif


uint32_t ADC1_read12(int channel, int sample_time) {
	return (ADC1_read16(channel, sample_time) >> 4);
}

/**********************************************************************/
// STM32F0 datasheet, 3.10.1 Temperature sensor
#define VREFINT_CAL_ADDR  ((uint16_t*) ((uint32_t)0x1FFFF7BA))
#define TEMP110_CAL_ADDR  ((uint16_t*) ((uint32_t)0x1FFFF7C2))
#define TEMP30_CAL_ADDR   ((uint16_t*) ((uint32_t)0x1FFFF7B8))

int32_t ADC1_read_TempSensor(int sample_time) {
  return ADC1_read16(ADC_Channel_TempSensor, sample_time);
}

int32_t ADC1_read_Vrefint(int sample_time) {
  return ADC1_read16(ADC_Channel_Vrefint, sample_time);
}

int32_t ADC1_convert_temperature(int32_t temp, int32_t vref) {
  int32_t temperature = (int64_t)temp * (*VREFINT_CAL_ADDR * (110000 - 30000)) / vref;
  temperature -= (*TEMP30_CAL_ADDR * (110000 - 30000));
  temperature /= (int32_t)(*TEMP110_CAL_ADDR - *TEMP30_CAL_ADDR);
  temperature += 30000;

  return temperature;  // Temperature in millidegrees C
}

int32_t ADC1_convert_vcc(int32_t vref) {
  int32_t vcc = ((3300 * 16 * (*VREFINT_CAL_ADDR)) / vref);
  return vcc;
}

/**********************************************************************/
