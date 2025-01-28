
#include <stdio.h>
#include "Core.h"
#include "ADC.h"

/**********************************************************************/
#define LED_PIN         2
#define LED_PORT        GPIOB
#define LED_PIN_SPEED   GPIO_Speed_2MHz

#define LED_LOW()       BITMASK_SET(LED_PORT->BRR,  _BV(LED_PIN))
#define LED_HIGH()      BITMASK_SET(LED_PORT->BSRR, _BV(LED_PIN))
#define LED_TOGGLE()    BITMASK_TGL(LED_PORT->ODR,  _BV(LED_PIN))

/**********************************************************************/
void GPIO_begin() {
  BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);             // enable AFIO clock
  BITMASK_SET(AFIO->MAPR,   AFIO_MAPR_SWJ_CFG_JTAGDISABLE);  // disable JTAG: free A15

  BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOB);           // enable GPIOB clock
  F103_GPIO_pinMode_output(LED_PORT, LED_PIN, GPIO_Mode_Out_PP | LED_PIN_SPEED);
}

/**********************************************************************/
int main(void) {
  /// Setup:
  Core_begin();
//  delay_ms(100);

  GPIO_begin();
  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();

  BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOA);    // enable GPIOA clock
  F103_GPIO_pinMode_input(GPIOA, 0, GPIO_Mode_AIN);

  ADC1_begin();
  ADC1_temp_sensor_begin();

  /// STM32F103 Datasheet
  #define  VREFINT    1.20    /// 5.3.4 Embedded reference voltage - Table 12. Embedded internal reference voltage
  #define  V25        1.43    /// 5.3.19 Temperature sensor characteristics - Table 50. TS characteristics
  #define  T25        25.0    /// 5.1.1 Minimum and maximum values - 5.1.2 Typical values
  #define  AVG_SLOPE  0.0043  /// 5.3.19 Temperature sensor characteristics - Table 50. TS characteristics

//    BITMASK_SET(ADC1->CR2, ADC_CR2_TSVREFE);
//    BITMASK_SET(ADC1->SMPR1, ADC_SMPR1_SMP17);

  /// Loop:
  while (1) {
    int Average  = 10;
    int vdd_sum    = 0;
    int vsense_sum = 0;
    for (int i = 0 ; i < Average ; i++)
    {
      int32_t adc_val16 = ADC1_read12(ADC_Channel_TempSensor, ADC_SampleTime_239_5Cycles) ;  // Select the ADCx_IN16 input channel
      int32_t adc_val17 = ADC1_read12(ADC_Channel_Vrefint,    ADC_SampleTime_239_5Cycles) ;  // Select the ADCx_IN17 input channel
//    int32_t adc_val16 = ADC1_read16(ADC_Channel_TempSensor, ADC_SampleTime_239_5Cycles)>> 4 ; /// Select the ADCx_IN16 input channel
//    int32_t adc_val17 = ADC1_read16(ADC_Channel_Vrefint, ADC_SampleTime_239_5Cycles)>> 4 ;    /// Select the ADCx_IN17 input channel
    // reading Vdd by utilising the internal 1.20V VREF
//    float tempr, vdd;
    //vdd = 1.20 * 4096.0 / adc_val17;
      int vdd     = 1024 * VREFINT * 4096.0 / adc_val17;
      int vsense  = 1024 * VREFINT * adc_val16 / adc_val17;
      vdd_sum     += vdd;
      vsense_sum  += vsense;
    }

    float vdd_average = vdd_sum / Average ;
    float vsense_average = vsense_sum / Average  ;
    // following 1.43 and 0.0043 parameters come from F103 datasheet - ch. 5.9.13
    // and need to be calibrated for every chip (large fab parameters variance)
    //tempr = (1.43 - (vdd / 4096.0 * adc_val16 )) / 0.0043 + 25.0;
    float tempr = ( V25 - (vsense_average/1024 ) )/ AVG_SLOPE  + T25 ; /// RM0008 Reference manual 11.10 Temperature sensor - Reading the temperature

    printf("temp = %.2f\t", tempr  );
    printf("vdd  = %.2f\n", vdd_average / 1024 );

    delay_ms(500);
//    LED_TOGGLE();
  }
}

