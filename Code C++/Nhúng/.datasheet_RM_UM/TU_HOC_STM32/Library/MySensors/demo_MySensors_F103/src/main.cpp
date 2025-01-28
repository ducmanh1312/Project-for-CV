
#include <stdio.h>      // printf

#include "Core.h"
#include "Watchdog.h"

#include "MySensors.h"
#include "MyCustoms.h"


/********************************************************************************/
int main() {
//  FLASH_Unlock();
//  FLASH_EraseAllPages();

  /// Setup:
  Core_begin();

  BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_AFIOEN);             // enable AFIO clock
  BITMASK_SET(AFIO->MAPR,   AFIO_MAPR_SWJ_CFG_JTAGDISABLE);  // disable JTAG (free A15)

  USART1_begin_A9A10(115200);

  main_mysensor();  // loop here
} // end main


/********************************************************************************/
void before() {
}


/********************************************************************************/
void presentation() {
  sendSketchInfo("MySensorsGW_STM32F103", "1.0");
}


/********************************************************************************/
void setup() {
  customReportFull();
}


/********************************************************************************/
uint32_t last_cmd_ms = 0;

void loop() {
//  uint32_t now_ms = millis();
//  if ( (now_ms - last_cmd_ms) >= (600000))  // 10 minute
//  {
//    last_cmd_ms = now_ms;
//    customReportFull();
//  }

//  CUSTOMLED_TOGGLE();
//  wait_process(100);

}


/********************************************************************************/
void receive(const MyMessage &message) {
//  printf("Rx_msg: ");
//  printf("sensor = %d", message.sensor);
//  printf(", ");
//  printf("type = %d", message.type);
//  printf(", ");
//  printf("status = %d", message.getBool());
//  printf(", ");
//  printf("string = %s", message.getString());
//  printf("\n");

  if (message.sender == 0) {  // gateway send
    switch (message.sensor) {
      case ID_CUSTOM:
        if (message.type == V_TEXT)
          customCommands(message.getString());
        break;
    }
  }
}


/********************************************************************************/

