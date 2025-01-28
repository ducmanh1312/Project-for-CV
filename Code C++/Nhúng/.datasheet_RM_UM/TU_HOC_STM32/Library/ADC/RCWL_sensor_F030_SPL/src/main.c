
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
uint32_t sqrt32(uint32_t x)
{
  uint32_t y = 0;
  for (uint32_t mask = 0x8000; mask > 0; mask >>= 1)
  {
    uint32_t t = y | mask;
    if (x > t*t) y = t;
  }
  return y;
}


/**********************************************************************/
// main
/**********************************************************************/
int main(void)
{
  /// Setup:
  Core_begin();

  USART1_begin_A9A10(BAUD_1M);
//  Core_PrintInfo();

  GPIO_begin();

  BITMASK_SET(RCC->AHBENR, RCC_AHBPeriph_GPIOA);
  F030_GPIO_pinMode_input(GPIOA, 2, GPIO_Mode_AN, GPIO_PuPd_NOPULL);

  ADC1_begin();

  const int Average     = 16;
  const int Timestep_ms = 20;

  const int x1_Smoothing = 256;           /// Exponential Smoothing Factor

  const int x2_Smoothing = 16;            /// Exponential Smoothing Factor
  const int x2_MaxValue  = 6000;

  const int Baseline_Smoothing = 2048;    /// Exponential Smoothing Factor
  const int Baseline_MaxValue  = 700;


  int next_delay = millis();
  int x1_mean = ADC1_read(ADC_Channel_2, ADC_SampleTime_13_5Cycles);

  int x2_mean = 0;

  int baseline = Baseline_MaxValue;
  int threshold = 0;

  int x4_sum = 0;


  /// Loop:
  while (1)
  {
    int x4_acc = 0;
    for (int i = 0; i < Average; i++)
    {
      printf("%d\t", x4_sum / Average);

      delay_until_ms(next_delay += Timestep_ms);

      int adcval = 0;
      adcval += ADC1_read(ADC_Channel_2, ADC_SampleTime_13_5Cycles);

      int x1 = adcval / 1;
      //printf("%d\t", x1);

      x1_mean += (x1 - x1_mean) / x1_Smoothing;
      //printf("%d\t", x1_mean);

      int x2 = x1 - x1_mean;
      x2 = abs(x2);
      x2 = min(x2, x2_MaxValue);
      //printf("%d\t", x2);

      x2_mean += (x2 - x2_mean) / x2_Smoothing;
      //printf("%d\t", x2_mean);

      if (baseline > x2_mean) baseline  =  x2_mean;
      else                    baseline += (x2_mean - baseline + Baseline_Smoothing/2) / Baseline_Smoothing;
      baseline = min(baseline, Baseline_MaxValue);
      //printf("%d\t", baseline);

      int x3 = x2_mean - baseline;
      printf("%d\t", x3);

      threshold = baseline * 3;

      printf("%d\t", baseline);
      printf("%d\t", threshold);

      printf("0 6000\n");
      //printf("\n");

      if (x3 > threshold) LED_HIGH();
      else                LED_LOW();

      x4_acc += x3;
    }
    x4_sum = x4_acc;
//    printf("%d\n", x4_sum);
  }
}

/**********************************************************************/


