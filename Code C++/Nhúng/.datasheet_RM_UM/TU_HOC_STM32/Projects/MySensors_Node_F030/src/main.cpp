
/********************************************************************************/

#include <stdlib.h>     // strtoul
#include <stdio.h>      // printf
#include <string.h>

#include "Core.h"
#include "Watchdog.h"
#include "ADC.h"
#include "MySensors.h"
#include "RF24_SPI_GPIO.h"
#include "MyCustoms.h"

/********************************************************************************/
/// Sơ đồ nối dây:

// CDS pin
#define RCWL_PIN   1
#define RCWL_PORT  GPIOA
#define RCWL_ADC   ADC_Channel_1

#define LIGHT_PIN   0
#define LIGHT_PORT  GPIOA
#define LIGHT_ADC   ADC_Channel_0


/// Chân UART: Core.h

/// Chân nRF24 (SPI + CSN + CE + IRQ): MySensors\drivers\RF24\RF24_SPI_GPIO.h

/// Chân Led: MySensors\core\MyCustoms.h

/********************************************************************************/
#define ID_COMBINE_0   (0x0B)
#define ID_COMBINE_1   (0x0C)
#define ID_COMBINE_2   (0x0D)

MyMessage msg_COMBINE_0(ID_COMBINE_0, V_TEXT);
MyMessage msg_COMBINE_1(ID_COMBINE_1, V_TEXT);
MyMessage msg_COMBINE_2(ID_COMBINE_2, V_TEXT);


/********************************************************************************/
int main() {
//  return 0;
//  FLASH_Unlock();
//  FLASH_EraseAllPages();

  /// Setup:
  Core_HSIConfig();
  Core_begin();

  /*--------------------------------------*/
  BITMASK_SET(RCC->AHBENR, RCC_AHBENR_GPIOAEN | RCC_AHBENR_GPIOBEN | RCC_AHBENR_GPIOFEN);  // enable clock GPIO
//  F030_GPIO_pinMode_output(RF24_CE_PORT, RF24_CE_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_2MHz);
//  RF24_CE_PORT->BRR  = _BV(RF24_CE_PIN);  // set CE = LOW
//  F030_GPIO_pinMode_output(RF24_CS_PORT, RF24_CS_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_2MHz);
//  RF24_CS_PORT->BSRR = _BV(RF24_CS_PIN);  // set CSN = HIGH

  /*--------------------------------------*/
  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();
  printf("\n########### STM32_main\n");

//printf("main_mysensor\n");
  main_mysensor();  // loop here
} // end main


/********************************************************************************/
void before() {
//  printf("Before\n");
}


/********************************************************************************/
void presentation() {
//  printf("Presentation\n");
  // Send the sketch version information to the gateway and Controller
//  sendSketchInfo("STM32F030", "1.0");

//  sprintf(buffer, "N%d_Combine", nodeID);
//  present(ID_COMBINE, S_INFO, buffer);
//
//  sprintf(buffer, "N%d_Combine_2", nodeID);
//  present(ID_COMBINE_2, S_INFO, buffer);
//
//  sprintf(buffer, "N%d_Startup", nodeID);
//  present(ID_NODE_INFO, S_INFO, buffer);
}



/********************************************************************************/
/* Temperature sensor calibration value address */
#define TEMP110_CAL_ADDR ((uint16_t*) ((uint32_t)0x1FFFF7C2))
#define TEMP30_CAL_ADDR  ((uint16_t*) ((uint32_t)0x1FFFF7B8))
#define VCC_CALIB       (1489)  // (1.3 * 4095.0 / 3.3)
//float temp_calib;

void internal_temp_sensor_begin() {
  ADC->CCR |= ADC_CCR_TSEN | ADC_CCR_VREFEN;  /// Temperature & VREF sensor enabled
//temp_calib = (float)(110 - 30) / (float)(*TEMP110_CAL_ADDR - *TEMP30_CAL_ADDR);
}


/********************************************************************************/
uint32_t sqrt32(uint32_t x) {
  uint32_t y = 0;
  for (uint32_t mask = 0x8000; mask > 0; mask >>= 1) {
    uint32_t t = y | mask;
    if (x > t*t) y = t;
  }
  return y;
}


/********************************************************************************/
const int Average = 500;
//const int Timestep_ms = 5;
const int Timestep_us = 5003;

const int vref_Smoothing = 32 * 1;           /// Exponential Smoothing Factor
int vref_avg = 0;
int vref_k = 128;
int vref_delta_baseline = 0;
int threshold = 0;

const int x1_Smoothing = 256 * 4;           /// Exponential Smoothing Factor
const int x2_Smoothing = 16 * 4;            /// Exponential Smoothing Factor
const int x2_MaxValue  = 7500;

const int Baseline_Smoothing = 2048;    /// Exponential Smoothing Factor
const int Baseline_MaxValue  = 700;

int next_delay;
int x1_mean_0 = 0;
int x2_mean_0 = 0;

//int x1_mean_1;
//int x2_mean_1 = 0;


/********************************************************************************/
void setup() {
  F030_GPIO_pinMode_input(LIGHT_PORT, LIGHT_PIN, GPIO_Mode_AN, GPIO_PuPd_NOPULL);
  F030_GPIO_pinMode_input(RCWL_PORT,   RCWL_PIN, GPIO_Mode_AN, GPIO_PuPd_NOPULL);

//  F030_GPIO_pinMode_input(GPIOA, 3, GPIO_Mode_AN, GPIO_PuPd_NOPULL);

  ADC1_begin();
  internal_temp_sensor_begin();

  //next_delay = millis();
  next_delay = micros();
  x1_mean_0  = ADC1_read16(RCWL_ADC, ADC_SampleTime_13_5Cycles);
//  x1_mean_1  = ADC1_read16(ADC_Channel_3, ADC_SampleTime_13_5Cycles);

  vref_avg   = (1*vref_k) * ADC1_read_Vrefint(ADC_SampleTime_239_5Cycles);

  printf("Setup done, Node ID = %d\n", getNodeId());

  customReport();
  wait_process(100);
  customReportFull();
  wait_process(100);

  customLedBlinkDisable();
}



/********************************************************************************/
typedef struct {
  uint16_t value;
} COMBINE_DATA;

COMBINE_DATA  combine_data[5];

#define SWAP_BYTE(x)    (uint16_t)(((x) >> 8) | ((x) << 8))

uint16_t crc16_update8(uint8_t data8) {
  static uint16_t crc = 0xFFFF;  // init value
  {
    crc  = (crc >> 8) | (crc << 8);
    crc ^= data8;
    crc ^= (crc & 0xFF) >> 4;
    crc ^= (crc << 12);
    crc ^= (crc & 0xFF) << 5;
  }
  return crc;
}

uint16_t crc16_update16(uint16_t data16) {
  //crc16_update8(data16 >> 0);
  //return crc16_update8(data16 >> 8);
  return crc16_update8((data16 >> 0) ^ (data16 >> 8));
}


/********************************************************************************/
extern bool RF24_sendFailed;
uint8_t RF24_lost_pkt    = 0;
int seq = -1;
uint32_t light_value_sum = 0;
uint32_t temperature_sum = 0;
uint16_t test_value_max = 0;

void read_sensors() {
  int light_sum = 0;
  int temp_sum = 0;
  int vref_sum = 0;

  int x3_max_0 = 0;
  int x3_max_1 = 0;

  int vref_delta_max = 0;
  static int BlackoutCounter = 0;

  static int prevTemp = 0;

  for (int i = 0; i < Average; i++) {
    hwWatchdogReset();
    //delay_until_ms(next_delay += Timestep_ms);
    //delay_us(crc16_update8(light_sum) & 0x03FF);  // random jitter sampling
    next_delay += Timestep_us;
    next_delay += -0x80 + (0x00FF & crc16_update16(temp_sum));  // random jitter sampling
    delay_until_us(next_delay);

    /*-----------------------------------*/
    ADC1_read16(ADC_Channel_15, ADC_SampleTime_28_5Cycles);       // reset ADC internals
    int temp   = ADC1_read_TempSensor(ADC_SampleTime_71_5Cycles);

    ADC1_read16(ADC_Channel_15, ADC_SampleTime_13_5Cycles);       // reset ADC internals
    int x1_0   = ADC1_read16(RCWL_ADC, ADC_SampleTime_55_5Cycles);

    ADC1_read16(ADC_Channel_15, ADC_SampleTime_13_5Cycles);       // reset ADC internals
    light_sum += ADC1_read16(LIGHT_ADC, ADC_SampleTime_41_5Cycles);

    ADC1_read16(ADC_Channel_15, ADC_SampleTime_13_5Cycles);       // reset ADC internals
    int vref   = ADC1_read_Vrefint(ADC_SampleTime_239_5Cycles);   // last ADC read

    int vref_delta = vref*vref_k - vref_avg;
    vref_avg += vref_delta / vref_Smoothing;

    //vref_delta_max = max(vref_delta_max, abs(vref_delta));
    vref_delta_max = max(vref_delta_max, -(vref_delta));
    //vref_delta_max = max(vref_delta_max, +(vref_delta));

    vref_sum += vref;
    temp_sum += temp;

    if (vref_delta > threshold) {
      BlackoutCounter = Average / 2;
      //BlackoutCounter = Average / 3;
    }

    if (BlackoutCounter > 0) {
      BlackoutCounter--;
    }

    /*-----------------------------------*/
    if (BlackoutCounter == 0) {
      x1_mean_0 += (x1_0 - x1_mean_0) / x1_Smoothing;

      if (x1_mean_0 == 0)
        x1_mean_0 = x1_0;

      int x2_0 = x1_0 - x1_mean_0;
      x2_0 = x2_0 * x2_0;

      x2_0 = min(x2_0, x2_MaxValue * x2_MaxValue);
      x2_mean_0 += (x2_0 - x2_mean_0) / x2_Smoothing;

      int x3_0 = x2_mean_0;
      x3_max_0 = max(x3_max_0, x3_0);
    }
  }

  customLedToggle();

  {
    vref_delta_baseline += (vref_delta_max - vref_delta_baseline) / 32;
    //threshold = 4 * vref_delta_baseline;
    threshold = 3 * vref_delta_baseline;
  }

  int16_t d0 = sqrt32(x3_max_0);
  d0 = min(d0, x2_MaxValue);

  uint16_t d1 = 0;
  d1 = min(d1, x2_MaxValue);

  /*--------------------------------------------------*/
  light_value_sum += (uint32_t)(light_sum / Average / 16);

  uint16_t test_value = vref_delta_max / 8;      // TESTING

  //printf("%d\n", ligh_value);

  /*--------------------------------------------------*/
  uint16_t temperature = ADC1_convert_temperature(temp_sum*1, vref_sum);

  temperature_sum += (uint32_t)(temperature);

  //printf("%04X  %d\n", temperature, temperature);
  int deltaTemp = prevTemp - (int)temperature;
  if (deltaTemp > (75)) {  //  x/1000 oC
    d1 = d0;
    //d0 = 0;
  }
  prevTemp = temperature;

  //test_value = min(test_value, x2_MaxValue);
  test_value = min(test_value, 4900);

  if (test_value_max < test_value)
    test_value_max = test_value;

  /*--------------------------------------------------*/
  // count lost pkt
  if (RF24_sendFailed) {
    RF24_lost_pkt += (RF->rf_retries >> 4) + 1;
  } else {
    RF24_disableIRQ();
    uint8_t rf24_observe = RF24_readByteRegister(RF24_OBSERVE_TX);
    RF24_enableIRQ();

    RF24_lost_pkt = rf24_observe & 0b1111;  // retransmit
  }

  /*--------------------------------------------------*/
  combine_data[0].value = SWAP_BYTE(d0);                       // RCWL
  combine_data[1].value = SWAP_BYTE((uint16_t)RF24_lost_pkt);  // Lost

  uint16_t send_value;
  seq = (seq + 1) % 3;

  switch (seq) {
    case 0:  // Light
        send_value = light_value_sum / 3;
        light_value_sum = 0;
        combine_data[2].value = SWAP_BYTE(send_value);
        send(msg_COMBINE_0.set(&combine_data, 6));
        break;

    case 1:  // Temp
        send_value = temperature_sum / 3;
        temperature_sum = 0;
        combine_data[2].value = SWAP_BYTE(send_value);
        send(msg_COMBINE_1.set(&combine_data, 6));
        break;

    case 2:  // Test
        combine_data[2].value = SWAP_BYTE(test_value_max);
        test_value_max = 0;
        send(msg_COMBINE_2.set(&combine_data, 6));
        break;
  }

  /*--------------------------------------------------*/
  delay_until_us(next_delay + Timestep_us - 1000);
  customLedToggle();
}


/********************************************************************************/
void loop() {
  read_sensors();
}


/********************************************************************************/
void receive(const MyMessage &message) {
//  printf("Rx_msg: ");
//  printf("sensor = %d", message.sensor);
//  printf(", ");
//  printf("type = %d", message.type);
//  printf(", ");
//  printf("string = %s", message.getString());
//  printf("\n");

  switch (message.sensor) {
    case ID_CUSTOM:
    case ID_COMBINE_0:
    case ID_COMBINE_1:
    case ID_COMBINE_2:
      if (message.type == V_TEXT)
        customCommands(message.getString());
      break;
  }
}

/********************************************************************************/
