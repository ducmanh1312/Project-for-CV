
#include <stdio.h>
#include "Core.h"

/**********************************************************************/
#include "Si4737_i2c.h"
Si4737 radio;

/// Sơ đồ nối dây:
//  Si4730     -----   STM32F103

/// Bắt buộc:
//  VDD (1)    -----   VCC (3V3)
//  VSS (3)    -----   GND
//  DIO (2)    -----   I2C1_SDA (B9)
//  CLK (10)   -----   I2C1_SCL (B8)
//  RST (9)    -----   GPIO (B15)

/// Không bắt buộc:
//  FMI (6)    -----   Antena
//  ROT (4)    -----   Right audio
//  LOT (5)    -----   Left audio


/**********************************************************************/
#define LED_PIN         2
#define LED_PORT        GPIOB
#define LED_PIN_SPEED   GPIO_Speed_2MHz

#define LED_LOW()       BITMASK_SET(LED_PORT->BRR,  _BV(LED_PIN))
#define LED_HIGH()      BITMASK_SET(LED_PORT->BSRR, _BV(LED_PIN))
#define LED_TOGGLE()    BITMASK_TOGGLE(LED_PORT->ODR, _BV(LED_PIN))

/**********************************************************************/
void GPIO_begin()
{
  BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);             // enable AFIO clock
  BITMASK_SET(AFIO->MAPR,   AFIO_MAPR_SWJ_CFG_JTAGDISABLE);  // disable JTAG: free A15

  BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOB);            // enable GPIOB clock
  F103_GPIO_pinMode_output(LED_PORT, LED_PIN, GPIO_Mode_Out_PP | LED_PIN_SPEED);
}


/**********************************************************************/
void getFrequency()
{
  bool goodtune;
  uint16_t frequency = radio.getFrequency(&goodtune);
  uint8_t mode = radio.getMode();

  printf("\n");
  printf("Currently tuned to ");
  switch(mode) {
    case SI4735_MODE_FM:
      printf("%d", frequency);
      printf(" MHz FM\n");
      break;
    case SI4735_MODE_AM:
      printf("%d", frequency);
      printf(" kHz AM\n");
      break;
    case SI4735_MODE_WB:
      printf("%d", frequency);
      printf(" MHz WB\n");
      break;
  }
  if (goodtune)
    printf("* Valid tune\n");
}


void getRSQ()
{
  #define LOOP  1
  Si4737_RX_Metrics RSQ[LOOP];

  for (int i = 0; i < LOOP; i++)
  {
    radio.getRSQ(&RSQ[i]);
  }


  for (int i = 0; i < LOOP; i++)
  {
    printf("\n");
    printf("Signal quality metrics %d:\n", i);

    printf("RSSI = %ddBuV", RSQ[i].RSSI);
    printf(", ");
    printf("SNR = %ddB", RSQ[i].SNR);
    printf("\n");

    if (radio.getMode() == SI4735_MODE_FM)
    {
      printf("%s", RSQ[i].PILOT ? "Stereo" : "Mono");
      printf(", ");
      printf("f-Offset = %dkHz", RSQ[i].FREQOFF);
      printf("\n");
    }
  }
}



void test_wire()
{
  uint8_t _response[16];
  uint16_t frequency = 0;
  uint32_t start = millis();

  for (int i = 0; i < 10; i++)
  {
    radio.sendCommand(SI4735_CMD_FM_TUNE_STATUS);
    radio.getResponse(_response);

    frequency = HL16(_response[2], _response[3]);
    printf("%d\n", frequency);
    frequency = 0;
  }

  uint32_t stop = millis();
  printf("Total time = %d\n", stop - start);
}

/**********************************************************************/
int main(void)
{
  /// Setup:
  Core_begin();
  delay(100);

  USART1_begin_A9A10(BAUD_1M);
//  Core_PrintInfo();
  GPIO_begin();
  printf("\n####################################\n");

  /*------------------------------------*/
  printf("Si4737 begin\n");
  uint32_t start = micros();
  radio.begin(SI4735_MODE_FM);
  uint32_t stop = micros();
  printf("Si4737 begin complete: %d\n", stop - start);

//	printf("STM32 code - Radio Powered up, FM mode\n");
	delay(100);  // Wait for Boot

  printf("Si4737 seekUp\n");
	radio.seekUp();
  printf("Si4737 seekUp complete\n");
  delay(3000);  // wait for seekUp

  radio.setVolume(55);
  getFrequency();

//  delay(1000);
//  radio.setFrequency(8900);
//  radio.setFrequency(9100);
  radio.setFrequency(10400);
  delay(10);
  getFrequency();

  test_wire();

  getRSQ();


  /// Loop:
  while (1)
  {
    LED_TOGGLE();
    delay(200);
  }
}
