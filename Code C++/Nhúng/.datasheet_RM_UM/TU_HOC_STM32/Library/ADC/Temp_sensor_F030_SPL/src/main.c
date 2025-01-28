
#include <stdio.h>
#include "Core.h"
#include "ADC.h"

/**********************************************************************/
#define LED_PIN         1
#define LED_PORT        GPIOA
#define LED_PIN_SPEED   GPIO_Speed_2MHz

#define LED_LOW()       BITMASK_SET(LED_PORT->BRR,  _BV(LED_PIN))
#define LED_HIGH()      BITMASK_SET(LED_PORT->BSRR, _BV(LED_PIN))
#define LED_TOGGLE()    BITMASK_TOGGLE(LED_PORT->ODR, _BV(LED_PIN))

/**********************************************************************/
void GPIO_begin()
{
  // enable GPIO clock
  BITMASK_SET(RCC->AHBENR, RCC_AHBPeriph_GPIOA | RCC_AHBPeriph_GPIOB);

  F030_GPIO_pinMode_output(LED_PORT, LED_PIN, GPIO_Mode_OUT, GPIO_OType_PP, LED_PIN_SPEED);
}


/**********************************************************************/
float vcc_read()
{
  #define V_REFINT  (1.2)  // STM32F0 datasheet, 6.3.4 Embedded reference voltage

  // đọc giá trị ADC của kênh Vrefint
  int adc_val = ADC1_read(ADC_Channel_Vrefint, ADC_SampleTime_239_5Cycles) >> 4;

  // tính điện áp hiện tại:
  float vcc = V_REFINT / (float)adc_val * 4095.0;
  return vcc;
}


void print_float_2digit(float number)
{
  int result = (int)(number * 100.0);  // làm tròn 2 chữ số

  if (result < 0.0)  // negative
  {
    printf("-");
    result = -result;
  }

  printf("%d", result / 100);
  printf(".");
  printf("%02d", result % 100);
  printf("\n");
}




/**********************************************************************/
// main
/**********************************************************************/
int main(void)
{
  /// Setup:
  Core_begin();

  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();

  GPIO_begin();


  ADC1_begin();
  ADC->CCR |= ADC_CCR_TSEN | ADC_CCR_VREFEN;  /// enable Temperature & VREF


  /// Loop:
  while (1)
  {
    const int Average = 10;
    int32_t tempAvg = 0;
    int32_t vrefintAvg = 0;

    for (int i = 0; i < Average; i++)
    {
      tempAvg    += ADC1_read_TempSensor(ADC_SampleTime_239_5Cycles);
      vrefintAvg += ADC1_read_Vrefint(ADC_SampleTime_239_5Cycles);
    }

    tempAvg    /= Average;
    vrefintAvg /= Average;

    int32_t temperature = ADC1_convert_temperature(tempAvg, vrefintAvg);
    int32_t vcc         = ADC1_convert_vcc(vrefintAvg);

    printf("%d\t", temperature );
    printf("%d\n", vcc);

    delay_ms(1000);
    LED_TOGGLE();
  }
}

/**********************************************************************/


