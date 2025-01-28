#include "Touch_F103.h"

/**********************************************************************/
#define TOUCH_BASELINE_N          (128L)
#define TOUCH_AVERAGE             (64 / 4)
#define TOUCH_THRESHOLD_DEFAULT   (500)
#define TOUCH_SKIP                (16)
#define TOUCH_NPIN                (16)

#define TOUCH_ADAPTIVE_THRESHOLD  (200)
#define TOUCH_ADAPTIVE_RATE       (32)

#define GPIO_MODE_OPP_2MHz        (0b0010)
#define GPIO_MODE_AIN             (0b0000)

/**********************************************************************/
int touch_base_line[TOUCH_NPIN];
int touch_threshold[TOUCH_NPIN];
uint32_t touch_mask;

/**********************************************************************/
int Touch_is_used(int touch_pin)
{
  if (touch_mask & _BV(touch_pin))
    return 1;

  return 0;
}

/**********************************************************************/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t Touch_A0_read_core()
{
  __NOP();
  /// B1: discharge the sampling cap and pullup to charge the External Cap
  ADC1->SQR3 = (uint32_t)DISCHARGE_CHANNEL;                        // rank = 1st
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  ADC1->DR;                                                        // Read data conversion

  /// B2: Select channel touch and read adc value
  ADC1->SQR3 = (uint32_t)ADC_Channel_0;                            // rank = 1st
  GPIOA->CRL &= ~(0b1111 << (4 * 0));                              // Analog input
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  GPIOA->CRL |= (GPIO_MODE_OPP_2MHz << (4 * 0));                   // Output Push_Pull
  return ADC1->DR;                                                 // Read data conversion
}

int __attribute__((aligned(16))) Touch_A0_read_raw()
{
  uint32_t value = 0;
  for (int i = 0; i < TOUCH_AVERAGE; i++)
  {
    value += Touch_A0_read_core();
    value += Touch_A0_read_core();
    value += Touch_A0_read_core();
    value += Touch_A0_read_core();
  }
  return value;
}

/**********************************************************************/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t Touch_A1_read_core()
{
  __NOP();
  /// B1: discharge the sampling cap and pullup to charge the External Cap
  ADC1->SQR3 = DISCHARGE_CHANNEL;
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  ADC1->DR;                                                        // Read data conversion

  /// B2: Select channel touch and read adc value
  ADC1->SQR3 = ADC_Channel_1;
  GPIOA->CRL &= ~(0b1111 << (4 * 1));                              // Analog input
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  GPIOA->CRL |= (GPIO_MODE_OPP_2MHz << (4 * 1));                   // Output Push_Pull
  return ADC1->DR;                                                 // Read data conversion
}

int __attribute__((aligned(16))) Touch_A1_read_raw()
{
  int value = 0;
  for (int i = 0; i < TOUCH_AVERAGE; i++)
  {
    value += Touch_A1_read_core();
    value += Touch_A1_read_core();
    value += Touch_A1_read_core();
    value += Touch_A1_read_core();
  }
  return value;
}

/**********************************************************************/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t Touch_A2_read_core()
{
  __NOP();
  /// B1: discharge the sampling cap and pullup to charge the External Cap
  ADC1->SQR3 = DISCHARGE_CHANNEL;
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  ADC1->DR;                                                        // Read data conversion

  /// B2: Select channel touch and read adc value
  ADC1->SQR3 = ADC_Channel_2;
  GPIOA->CRL &= ~(0b1111 << (4 * 2));                              // Analog input
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  GPIOA->CRL |= (GPIO_MODE_OPP_2MHz << (4 * 2));                   // Output Push_Pull
  return ADC1->DR;                                                 // Read data conversion
}

int __attribute__((aligned(16))) Touch_A2_read_raw()
{
  int value = 0;
  for (int i = 0; i < TOUCH_AVERAGE; i++)
  {
    value += Touch_A2_read_core();
    value += Touch_A2_read_core();
    value += Touch_A2_read_core();
    value += Touch_A2_read_core();
  }
  return value;
}

/**********************************************************************/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t Touch_A3_read_core()
{
  __NOP();
  /// B1: discharge the sampling cap and pullup to charge the External Cap
  ADC1->SQR3 = DISCHARGE_CHANNEL;
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  ADC1->DR;                                                        // Read data conversion

  /// B2: Select channel touch and read adc value
  ADC1->SQR3 = ADC_Channel_3;
  GPIOA->CRL &= ~(0b1111 << (4 * 3));                              // Analog input
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  GPIOA->CRL |= (GPIO_MODE_OPP_2MHz << (4 * 3));                   // Output Push_Pull
  return ADC1->DR;                                                 // Read data conversion
}

int __attribute__((aligned(16))) Touch_A3_read_raw()
{
  int value = 0;
  for (int i = 0; i < TOUCH_AVERAGE; i++)
  {
    value += Touch_A3_read_core();
    value += Touch_A3_read_core();
    value += Touch_A3_read_core();
    value += Touch_A3_read_core();
  }
  return value;
}

/**********************************************************************/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t Touch_A4_read_core()
{
  __NOP();
  /// B1: discharge the sampling cap and pullup to charge the External Cap
  ADC1->SQR3 = DISCHARGE_CHANNEL;
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  ADC1->DR;                                                        // Read data conversion

  /// B2: Select channel touch and read adc value
  ADC1->SQR3 = ADC_Channel_4;
  GPIOA->CRL &= ~(0b1111 << (4 * 4));                              // Analog input
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  GPIOA->CRL |= (GPIO_MODE_OPP_2MHz << (4 * 4));                   // Output Push_Pull
  return ADC1->DR;                                                 // Read data conversion
}

int __attribute__((aligned(16))) Touch_A4_read_raw()
{
  int value = 0;
  for (int i = 0; i < TOUCH_AVERAGE; i++)
  {
    value += Touch_A4_read_core();
    value += Touch_A4_read_core();
    value += Touch_A4_read_core();
    value += Touch_A4_read_core();
  }
  return value;
}

/**********************************************************************/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t Touch_A5_read_core()
{
  __NOP();
  /// B1: discharge the sampling cap and pullup to charge the External Cap
  ADC1->SQR3 = DISCHARGE_CHANNEL;
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  ADC1->DR;                                                        // Read data conversion

  /// B2: Select channel touch and read adc value
  ADC1->SQR3 = ADC_Channel_5;
  GPIOA->CRL &= ~(0b1111 << (4 * 5));                              // Analog input
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  GPIOA->CRL |= (GPIO_MODE_OPP_2MHz << (4 * 5));                   // Output Push_Pull
  return ADC1->DR;                                                 // Read data conversion
}

int __attribute__((aligned(16))) Touch_A5_read_raw()
{
  int value = 0;
  for (int i = 0; i < TOUCH_AVERAGE; i++)
  {
    value += Touch_A5_read_core();
    value += Touch_A5_read_core();
    value += Touch_A5_read_core();
    value += Touch_A5_read_core();
  }
  return value;
}

/**********************************************************************/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t Touch_A6_read_core()
{
  __NOP();
  /// B1: discharge the sampling cap and pullup to charge the External Cap
  ADC1->SQR3 = DISCHARGE_CHANNEL;
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  ADC1->DR;                                                        // Read data conversion

  /// B2: Select channel touch and read adc value
  ADC1->SQR3 = ADC_Channel_6;
  GPIOA->CRL &= ~(0b1111 << (4 * 6));                              // Analog input
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  GPIOA->CRL |= (GPIO_MODE_OPP_2MHz << (4 * 6));                   // Output Push_Pull
  return ADC1->DR;                                                 // Read data conversion
}

int __attribute__((aligned(16))) Touch_A6_read_raw()
{
  int value = 0;
  for (int i = 0; i < TOUCH_AVERAGE; i++)
  {
    value += Touch_A6_read_core();
    value += Touch_A6_read_core();
    value += Touch_A6_read_core();
    value += Touch_A6_read_core();
  }
  return value;
}


/**********************************************************************/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t Touch_A7_read_core()
{
  __NOP();
  /// B1: discharge the sampling cap and pullup to charge the External Cap
  ADC1->SQR3 = DISCHARGE_CHANNEL;
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  ADC1->DR;                                                        // Read data conversion

  /// B2: Select channel touch and read adc value
  ADC1->SQR3 = ADC_Channel_7;
  GPIOA->CRL &= ~(0b1111 << (4 * 7));                              // Analog input
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  GPIOA->CRL |= (GPIO_MODE_OPP_2MHz << (4 * 7));                   // Output Push_Pull
  return ADC1->DR;                                                 // Read data conversion
}

int __attribute__((aligned(16))) Touch_A7_read_raw()
{
  int value = 0;
  for (int i = 0; i < TOUCH_AVERAGE; i++)
  {
    value += Touch_A7_read_core();
    value += Touch_A7_read_core();
    value += Touch_A7_read_core();
    value += Touch_A7_read_core();
  }
  return value;
}


/**********************************************************************/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t Touch_B0_read_core()
{
  __NOP();
  /// B1: discharge the sampling cap and pullup to charge the External Cap
  ADC1->SQR3 = DISCHARGE_CHANNEL;
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  ADC1->DR;                                                        // Read data conversion

  /// B2: Select channel touch and read adc value
  ADC1->SQR3 = ADC_Channel_8;
  GPIOB->CRL &= ~(0b1111 << (4 * 0));                              // Analog input
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  GPIOB->CRL |= (GPIO_MODE_OPP_2MHz << (4 * 0));                   // Output Push_Pull
  return ADC1->DR;                                                 // Read data conversion
}

int __attribute__((aligned(16))) Touch_B0_read_raw()
{
  int value = 0;
  for (int i = 0; i < TOUCH_AVERAGE; i++)
  {
    value += Touch_B0_read_core();
    value += Touch_B0_read_core();
    value += Touch_B0_read_core();
    value += Touch_B0_read_core();
  }
  return value;
}

/**********************************************************************/
__attribute__( ( always_inline ) ) __STATIC_INLINE uint32_t Touch_B1_read_core()
{
  __NOP();
  /// B1: discharge the sampling cap and pullup to charge the External Cap
  ADC1->SQR3 = DISCHARGE_CHANNEL;
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  ADC1->DR;                                                        // Read data conversion

  /// B2: Select channel touch and read adc value
  ADC1->SQR3 = ADC_Channel_9;
  GPIOB->CRL &= ~(0b1111 << (4 * 1));                              // Analog input
  ADC1->CR2  = ADC_ExternalTrigConv_None | ADC_CR2_ADON;           // Start conversion
  while ((ADC1->SR & ADC_FLAG_EOC) == 0);                          // Wait end of conversion
  GPIOB->CRL |= (GPIO_MODE_OPP_2MHz << (4 * 1));                   // Output Push_Pull
  return ADC1->DR;                                                 // Read data conversion
}

int __attribute__((aligned(16))) Touch_B1_read_raw()
{
  uint32_t value = 0;

  for (int i = 0; i < TOUCH_AVERAGE; i++)
  {
    value += Touch_B1_read_core();
    value += Touch_B1_read_core();
    value += Touch_B1_read_core();
    value += Touch_B1_read_core();
  }
  return value;
}


/**********************************************************************/
int Touch_dummy()
{
  return 0;
}

// array of function pointers
int (*Touch_read_raw[TOUCH_NPIN])() =
{
  &Touch_A0_read_raw,
  Touch_A1_read_raw,
  Touch_A2_read_raw,
  Touch_A3_read_raw,
  Touch_A4_read_raw,
  Touch_A5_read_raw,
  Touch_A6_read_raw,
  Touch_A7_read_raw,
  Touch_B0_read_raw,
  Touch_B1_read_raw,
  Touch_dummy,
  Touch_dummy,
  Touch_dummy,
  Touch_dummy,
  Touch_dummy,
  Touch_dummy,
};

/**********************************************************************/
int Touch_read(int touch_pin)
{
  touch_pin &= 0x0F;
//  return ( ((*Touch_read_raw[touch_pin])() - touch_base_line[touch_pin]) / TOUCH_AVERAGE);

  int read = ((*Touch_read_raw[touch_pin])() - touch_base_line[touch_pin]) / TOUCH_AVERAGE;
  if (read < TOUCH_ADAPTIVE_THRESHOLD)
    touch_base_line[touch_pin] += read / ((read < 0) ? (TOUCH_ADAPTIVE_RATE) : (TOUCH_ADAPTIVE_RATE * 2));

  return read;
}

/**********************************************************************/
int Touch_read_state(int touch_pin)
{
  touch_pin &= 0x0F;
  return (Touch_read(touch_pin) > touch_threshold[touch_pin]) ? 1 : 0;
}

/**********************************************************************/
void Touch_calibrate()
{
  // 1. Skip:
  for (int touch_pin = 0; touch_pin < TOUCH_NPIN; touch_pin++)
  {
    for (int i = 0; i < TOUCH_SKIP; i++)
      (*Touch_read_raw[touch_pin])();
  }

  // 2. Read baseline:
  for (int touch_pin = 0; touch_pin < TOUCH_NPIN; touch_pin++)
  {
    uint64_t sum_baseline = 0;
    for (int i = 0; i < TOUCH_BASELINE_N; i++)
      sum_baseline += (*Touch_read_raw[touch_pin])();

    touch_base_line[touch_pin] = (sum_baseline + TOUCH_BASELINE_N / 2) / TOUCH_BASELINE_N;
  }
}

/**********************************************************************/
int Touch_get_base_line(int touch_pin)
{
  return touch_base_line[touch_pin & 0x0F];
}

/**********************************************************************/
void Touch_set_threshhold(int touch_pin, int threshold)
{
  touch_threshold[touch_pin & 0x0F] = threshold;
}

/**********************************************************************/
#define ADC_CFG_SAMPLE_TIME(channel, s_time) (ADC1->SMPR2 = (ADC1->SMPR2 & ~(0b111 << (3*(channel)))) | ((s_time) << (3*(channel))))

void Touch_begin(uint32_t mask)
{
  touch_mask = mask & (_BV(TOUCH_NPIN) - 1);

  // Enable Clock GPIO
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB, ENABLE);

  // Discharge channel:
  GPIO_InitTypeDef GPIO_InitStructure;
  GPIO_InitStructure.GPIO_Pin   = _BV(DISCHARGE_PIN);
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_2MHz;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AIN;
  GPIO_Init(DISCHARGE_PORT, &GPIO_InitStructure);

  // Touch channel:
  for (int touch_pin = TOUCH_PIN_A0; touch_pin <= TOUCH_PIN_A7; touch_pin++)  // port A
  {
    if (Touch_is_used(touch_pin))
    {
      GPIOA->ODR |= _BV(touch_pin);  // set HIGH level (when output mode)
      Touch_set_threshhold(touch_pin, TOUCH_THRESHOLD_DEFAULT);
      ADC_CFG_SAMPLE_TIME(touch_pin, ADC_SampleTime_1Cycles5);
    }
    else
      Touch_read_raw[touch_pin] = &Touch_dummy;
  }

  for (int touch_pin = TOUCH_PIN_B0; touch_pin <= TOUCH_PIN_B1; touch_pin++)  // port B
  {
    if (Touch_is_used(touch_pin))
    {
      GPIOB->ODR |= _BV(touch_pin - 8);  // set HIGH level (when output mode)
      Touch_set_threshhold(touch_pin, TOUCH_THRESHOLD_DEFAULT);
      ADC_CFG_SAMPLE_TIME(touch_pin, ADC_SampleTime_1Cycles5);
    }
    else
      Touch_read_raw[touch_pin] = &Touch_dummy;
  }

  // PCLK2 is the APB2 clock
  RCC_ADCCLKConfig(RCC_PCLK2_Div2);                     // ADCCLK = PCLK2/2 = 72/2 = 36MHz
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);  // enable clock ADC1
  ADC_DeInit(ADC1);

  // ------------------------------ ADC1 Configuration ---------------------------------
  ADC_InitTypeDef  ADC_InitStructure;
  ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;   // ADC1 and ADC2 operate independently
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;        // Disable the scan conversion so we do one at a time
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;  // Disable ADC_ContinuousConvMode
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfChannel = 1;              // Cau hinh so kenh ADC regular su dung
  ADC_Init(ADC1, &ADC_InitStructure);            // Setup ADC1

  ADC_Cmd(ADC1, ENABLE);                         // Enable ADC1
  ADC_ResetCalibration(ADC1);                    // Reset thanh ghi hieu chinh ADC1
  while(ADC_GetResetCalibrationStatus(ADC1));    // Cho qua trinh Reset ket thuc
  ADC_StartCalibration(ADC1);                    // Bat dau hieu chinh ADC1
  while(ADC_GetCalibrationStatus(ADC1));         // Cho den khi hieu chinh ADC ket thuc

  Touch_calibrate();
}

/**********************************************************************/
