#include <stdio.h>      // printf

#include "Core.h"
#include "Watchdog.h"

#include "MySensors.h"
#include "MyCustoms.h"


/********************************************************************************/
#define ID_COMBINE_0   (0x0B)
#define ID_COMBINE_1   (0x0C)
#define ID_COMBINE_2   (0x0D)

MyMessage msg_COMBINE_0(ID_COMBINE_0, V_TEXT);
MyMessage msg_COMBINE_1(ID_COMBINE_1, V_TEXT);
MyMessage msg_COMBINE_2(ID_COMBINE_2, V_TEXT);

/********************************************************************************/
int main() {
//  FLASH_Unlock();
//  FLASH_EraseAllPages();

  /// Setup:
  Core_begin();

  BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);             // enable AFIO clock
  BITMASK_SET(AFIO->MAPR,   AFIO_MAPR_SWJ_CFG_JTAGDISABLE);  // disable JTAG (free A15)

  USART1_begin_A9A10(BAUD_1M);
  Core_PrintInfo();
  printf("\n########### STM32_main\n");

  main_mysensor();  // loop here
} // end main


/********************************************************************************/
void before() {
}


/********************************************************************************/
void presentation() {
//  sendSketchInfo("Node_STM32F103", "1.0");
}


/********************************************************************************/
void setup() {
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

COMBINE_DATA  combine_data[3];

#define SWAP_BYTE(x)    (uint16_t)(((x) >> 8) | ((x) << 8))

int next_delay;
const int Timestep_us = 500003;

int seq = -1;



void read_sensors() {
  combine_data[0].value = SWAP_BYTE(1111);
  combine_data[1].value = SWAP_BYTE(2222);

  uint16_t send_value;
  seq = (seq + 1) % 3;

  switch (seq) {
    case 0:  // Light
        combine_data[2].value = SWAP_BYTE(3333);
        send(msg_COMBINE_0.set(&combine_data, 6));
        break;

    case 1:  // Temp
        combine_data[2].value = SWAP_BYTE(4444);
        send(msg_COMBINE_1.set(&combine_data, 6));
        break;

    case 2:  // Test
        combine_data[2].value = SWAP_BYTE(5555);
        send(msg_COMBINE_2.set(&combine_data, 6));
        break;
  }

  wait_process(1000);
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
