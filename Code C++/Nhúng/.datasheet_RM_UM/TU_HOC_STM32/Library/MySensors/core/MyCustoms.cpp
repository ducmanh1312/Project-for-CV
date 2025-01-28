
#include <string.h>
#include <stdlib.h>     // strtoul
#include <stdio.h>
#include "Core.h"

#include "MyCustoms.h"

#include "RF24_SPI_GPIO.h"

#include "MyEepromAddresses.h"
#include "MyTransport.h"

#include "FStore.h"
#include "Watchdog.h"

/********************************************************************************/
#define MYSENSOR_FSTORE_ID        (50)

// dùng 2 page Flash cuối cùng
#define MYSENSOR_FSTORE_NUM_PAGE  (2)

#ifdef STM32F10X_MD
  #define MYSENSOR_START_ADDR     ((uint32_t)0x0801F800)  // page 126 & 127
#endif

#ifdef STM32F0XX
  #define MYSENSOR_START_ADDR     ((uint32_t)0x08007800)  // page 30, 31
#endif

FStore  FStoreMysensor;

/********************************************************************************/
#define MAX_RETRY_CONFIG    3

int retry_config_counter = 1;

/********************************************************************************/
#define SIZE_CONFIG_RF            (sizeof(CUSTOM_CONFIG))

#define OFFSET_CONFIG_RFA         (EEPROM_LOCAL_CONFIG_ADDRESS)  // start
#define OFFSET_CONFIG_RFB         (OFFSET_CONFIG_RFA + SIZE_CONFIG_RF)
#define OFFSET_RFCONFIG_ACTIVE    (OFFSET_CONFIG_RFB + SIZE_CONFIG_RF)

#define RFCONFIG_ACTIVE_A   0
#define RFCONFIG_ACTIVE_B   1

/********************************************************************************/
const CUSTOM_CONFIG ConfigRFDefault = {
  MY_RF24_CONFIGURATION,
  MY_RF24_ADDR_WIDTH,
  MY_RF24_RETRIES,
  MY_RF24_CHANNEL,
  MY_RF24_RF_SETUP,
 {MY_RF24_BASE_RADIO_ID},
};

CUSTOM_CONFIG  ConfigRFA  __attribute__ ((aligned (16)));
CUSTOM_CONFIG  ConfigRFB  __attribute__ ((aligned (16)));
CUSTOM_CONFIG  *RF, *RF2;

/********************************************************************************/
//void printConfig(CUSTOM_CONFIG *cfg) {
//  printf("%02X ", cfg->rf_config);
//  printf("%02X ", cfg->rf_aw);
//  printf("%02X ", cfg->rf_retries);
//  printf("%02X ", cfg->rf_channel);
//  printf("%02X ", cfg->rf_setup);
//  for (int i = 0; i < 5; i++)
//    printf(" %02X", cfg->rf_addr[i]);
//  printf("\n");
//}


/********************************************************************************/
void customLoadConfig() {
  FStore_ReadStruct(&FStoreMysensor, &ConfigRFA, SIZE_CONFIG_RF, OFFSET_CONFIG_RFA, &ConfigRFDefault);
  FStore_ReadStruct(&FStoreMysensor, &ConfigRFB, SIZE_CONFIG_RF, OFFSET_CONFIG_RFB, &ConfigRFDefault);

  switch (hwReadByte(OFFSET_RFCONFIG_ACTIVE)) {
    case RFCONFIG_ACTIVE_A: RF = &ConfigRFA; RF2 = &ConfigRFB; break;
    default:                RF = &ConfigRFB; RF2 = &ConfigRFA;
                            hwWriteByte(OFFSET_RFCONFIG_ACTIVE, RFCONFIG_ACTIVE_B);
  }

//  printConfig(RF);
//  printConfig(RF2);
}


/********************************************************************************/
void customSaveConfig() {
  FStore_SaveStruct(&FStoreMysensor, &ConfigRFA, SIZE_CONFIG_RF, OFFSET_CONFIG_RFA);
  FStore_SaveStruct(&FStoreMysensor, &ConfigRFB, SIZE_CONFIG_RF, OFFSET_CONFIG_RFB);
}


/********************************************************************************/
void customSwitchRFActive() {
  switch (hwReadByte(OFFSET_RFCONFIG_ACTIVE)) {
    case RFCONFIG_ACTIVE_B:
      hwWriteByte(OFFSET_RFCONFIG_ACTIVE, RFCONFIG_ACTIVE_A);
      RF = &ConfigRFA; RF2 = &ConfigRFB;
      break;

    default:
      hwWriteByte(OFFSET_RFCONFIG_ACTIVE, RFCONFIG_ACTIVE_B);
      RF = &ConfigRFB; RF2 = &ConfigRFA;
  }

  retry_config_counter = 1;  // clear
}


/********************************************************************************/
void customRetryConfig() {
  if (retry_config_counter++ > MAX_RETRY_CONFIG) {
    retry_config_counter = 1;

    CUSTOM_CONFIG *RFtmp = RF;
    RF  = RF2;
    RF2 = RFtmp;
  }
}


/********************************************************************************/
uint8_t hex2num(char c) {
  return (c >= 'A') ?  (c - ('A' - 10)) : (c - '0');
}


/********************************************************************************/
void customConfigRF_TxPower(const char *str) {
  uint8_t level = hex2num(str[0]);
  RF->rf_setup = (RF->rf_setup & ~(_BV(RF24_RF_PWR_HIGH) | _BV(RF24_RF_PWR_LOW))) | (level << 1);

//  printf("New SETUP: %02X\n", ConfigRF.rf_setup);
  NVIC_DisableIRQ(RF24_IRQ);  /// disable RF24_irqHandler
  RF24_setRFSetup(RF->rf_setup);
  NVIC_EnableIRQ(RF24_IRQ);   /// enable RF24_irqHandler

  customSaveConfig();
}


/********************************************************************************/
void customConfigRF_TxRetry(const char *str) {
  // max:
  if (str[0] != ' ') {
    uint8_t arc = hex2num(str[0]);
    RF->rf_retries = (RF->rf_retries & ~(0b1111 << RF24_ARC)) | (arc << RF24_ARC);
  }

  // timeout:
  if (str[1] != ' ') {
    uint8_t ard = hex2num(str[1]);
    RF->rf_retries = (RF->rf_retries & ~(0b1111 << RF24_ARD)) | (ard << RF24_ARD);
  }

//  printf("New retries: %02X\n", ConfigRF.rf_retries);
  NVIC_DisableIRQ(RF24_IRQ);  /// disable RF24_irqHandler
  RF24_setRETR(RF->rf_retries);
  NVIC_EnableIRQ(RF24_IRQ);   /// enable RF24_irqHandler

  customSaveConfig();
}


/********************************************************************************/
void customConfigRF2_TxPower(const char *str)
{
  uint8_t level = hex2num(str[0]);
  RF2->rf_setup = (RF2->rf_setup & ~(_BV(RF24_RF_PWR_HIGH) | _BV(RF24_RF_PWR_LOW))) | (level << 1);
  customSaveConfig();
}


/********************************************************************************/
void customConfigRF2_TxRetry(const char *str) {
  // max:
  if (str[0] != ' ') {
    uint8_t arc = hex2num(str[0]);
    RF2->rf_retries = (RF2->rf_retries & ~(0b1111 << RF24_ARC)) | (arc << RF24_ARC);
  }

  // timeout:
  if (str[1] != ' ') {
    uint8_t ard = hex2num(str[1]);
    RF2->rf_retries = (RF2->rf_retries & ~(0b1111 << RF24_ARD)) | (ard << RF24_ARD);
  }

  customSaveConfig();
}


/********************************************************************************/
void customConfigRF2_CBA(const char *str) {
  // Channel:
  if (str[0] != ' ') {
    const char str_channel[3] = {str[0], str[1], '\0'};
    uint8_t ch = strtoul(str_channel, NULL, 16);
    RF2->rf_channel = ch;
    printf("New RF2 channel = %d\n", ch);
  }

  // Baud:
  if (str[2] != ' ') {
    uint8_t baud = hex2num(str[2]);
    RF2->rf_setup = (RF2->rf_setup & ~(_BV(RF24_RF_DR_LOW) | _BV(RF24_RF_DR_HIGH)))
                  | ((baud & 0b10) << 4) | ((baud & 0b01) << RF24_RF_DR_HIGH);
    printf("New RF2 baud = %d\n", baud);
  }

  // Address:
  if (strlen(str) > 3) {
    const char *str_addr = str + 3;  // skip channel, baud
    //printf("New RF2 addr = [%s]\n", str_addr);

    int len = strlen(str_addr);
  //printf("New Addr: %s, len = %d\n", str, len);

    char buff[3];
    buff[2] = '\0';
    int addr_width = len >> 1;
    uint8_t addr_new[addr_width];

    for (int i = 0; i < len; i += 2) {
      buff[0] = str_addr[i + 0];
      buff[1] = str_addr[i + 1];
      addr_new[i >> 1] = strtoul(buff, NULL, 16);
    }

    printf("New RF2 addr = ", str_addr);
    for (int i = 0; i < addr_width; i++)
      printf("%02X", addr_new[i]);
    printf("\n");

    RF2->rf_aw = addr_width;
    for (int i = 0; i < addr_width; i++)
      RF2->rf_addr[i] = addr_new[i];
  }

  customSaveConfig();
}



/********************************************************************************/
void customMysensorReconnect() {
	// Initialise transport layer
	transportInitialize();

	// wait until transport is ready
	(void)transportWaitUntilReady(MY_TRANSPORT_WAIT_READY_MS);
}


/********************************************************************************/
void customConfigRF2_Active() {
  printf("rf2_active\n");
  customSwitchRFActive();

  customMysensorReconnect();
}


/********************************************************************************/
void customRenewID() {
  printf("Renew node ID\n");
  hwWriteConfig(EEPROM_NODE_ID_ADDRESS, 255);  // clear node id
  customMysensorReconnect();
  customReportFull();
}


/********************************************************************************/
void customRenewParent() {
  printf("Find parent\n");
  hwWriteConfig(EEPROM_PARENT_NODE_ID_ADDRESS, 255);  // clear parent node id
  customMysensorReconnect();
  customReportFull();
}


/********************************************************************************/
void customLedBlinkEnable() {

  #ifdef STM32F10X_MD
    BITMASK_SET(RCC->APB2ENR, RCC_APB2Periph_GPIOB);            // enable GPIOB clock
    F103_GPIO_pinMode_output(CUSTOMLED_PORT, CUSTOMLED_PIN, GPIO_Mode_Out_PP | GPIO_Speed_2MHz);
  #endif


  #ifdef STM32F0XX
    if (TIM1->CR1 != 0)
      return;

    // enable GPIO clock
    BITMASK_SET(RCC->AHBENR, F030_GPIO_get_rcc_clock_mask(CUSTOMLED_PORT));

    // TIM1_config PWM
    BITMASK_SET(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);  // Enable clock

    TIM1->PSC = 48000;  // Prescaler
    TIM1->ARR = 250;    // Auto-reload

//    /// OC3:
//    TIM1->CCR3  = 50;
//    TIM1->CCMR2 = TIM_OCMode_PWM2 << 0;
//    TIM1->CCER  = TIM_CCER_CC3E;
//    F030_GPIO_pinAF_select(GPIOA, 10, GPIO_AF_2);
//    F030_GPIO_pinMode_output(GPIOA, 10, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_2MHz);

    /// OC3N:
    TIM1->CCR3  = 50;
    TIM1->CCMR2 = TIM_OCMode_PWM2 << 0;
    TIM1->CCER  = TIM_CCER_CC3NE;
    F030_GPIO_pinAF_select(CUSTOMLED_PORT, CUSTOMLED_PIN, GPIO_AF_2);
    F030_GPIO_pinMode_output(CUSTOMLED_PORT, CUSTOMLED_PIN, GPIO_Mode_AF, GPIO_OType_PP, GPIO_Speed_2MHz);

    TIM1->BDTR = TIM_BDTR_MOE   // main output enable
               | TIM_BDTR_AOE;  // automatic output enable
    TIM1->CR1 = TIM_CR1_CEN;    // TIM1 enable: start PWM
  #endif
}


/********************************************************************************/
void customLedBlinkDisable() {

  #ifdef STM32F0XX
    TIM1->CR1 = 0;  // TIM1 disable
    BITMASK_CLEAR(RCC->APB2ENR, RCC_APB2ENR_TIM1EN);  // disable clock
    F030_GPIO_pinMode_output(CUSTOMLED_PORT, CUSTOMLED_PIN, GPIO_Mode_OUT, GPIO_OType_PP, GPIO_Speed_2MHz);
  #endif

  CUSTOMLED_LOW();
}


/********************************************************************************/
MyMessage msg_Custom(ID_CUSTOM, V_TEXT);

//char base_report_msg[10];

uint16_t UID;
uint8_t reset_type = 9;  // init: unknow type

//void customBaseReport() {
//  UID = Core_GetUid16();
//
//  int reset_type = 9;  // init: unknow type
//  ResetFlags_Begin();
//
//       if (ResetFlags_Check(RESET_FLAG_POWER))                reset_type = 0;
//  else if (ResetFlags_Check(RESET_FLAG_LOW_POWER))            reset_type = 1;
//  else if (ResetFlags_Check(RESET_FLAG_WATCHDOG_WINDOWN))     reset_type = 2;
//  else if (ResetFlags_Check(RESET_FLAG_WATCHDOG_INDEPENDENT)) reset_type = 3;
//  else if (ResetFlags_Check(RESET_FLAG_SOFTWARE))             reset_type = 4;
//  else if (ResetFlags_Check(RESET_FLAG_NRST_PIN))             reset_type = 5;
//
//  sprintf(base_report_msg, "%1X%1X%02X%04X", reset_type,
//                                             FStore_CountPageErase(&FStoreMysensor),
//                                             FStore_CountKeyUsed(&FStoreMysensor),
//                                             UID);
//}


/********************************************************************************/
//void customReportStartup() {
//  char startup_report[25];
//
//  uint8_t rf_setup = ((RF->rf_setup >> 1) & 0b111)     // bit 3,2,1
//                   | ((RF->rf_setup & _BV(5)) >> 2);   // bit 5
//
//  sprintf(startup_report, "%s%02X%04X%1X%02X",
//          base_report_msg,
//          getParentNodeId(),
//          millis() / 60000,   // uptime_minute
//          rf_setup,
//          RF->rf_retries
//          );
//
//  printf("Report startup: [%s]\n", startup_report);
//  send(msg_Custom.set(startup_report));
//
//  CUSTOMLED_TOGGLE();
//}


/********************************************************************************/
#ifdef MY_GATEWAY_SERIAL

  void customReportFull() {
    char full_report_msg[25];

    uint16_t uptime_minute = millis() / 60000;

    uint16_t rf24_addr = ((uint16_t)(RF->rf_addr[1]) << 8) | RF->rf_addr[0];

    sprintf(full_report_msg, "%04X%02X%02X%02X%02X%02X%04X",
          uptime_minute,
          RF->rf_config,
          RF->rf_aw,
          RF->rf_retries,
          RF->rf_channel,
          RF->rf_setup,
          rf24_addr
    );

    send(msg_Custom.set(full_report_msg));
  }

#endif


#ifndef MY_GATEWAY_SERIAL

  void customReportFull() {
    char full_report_msg[25];

    uint8_t rf_setup = ((RF->rf_setup >> 1) & 0b111)     // bit 3,2,1
                     | ((RF->rf_setup & _BV(5)) >> 2);   // bit 5

    sprintf(full_report_msg, "%1X%02X%1X%1X%02X%02X%1X%02X%02X%02X%02X%02X",
            FStore_CountPageErase(&FStoreMysensor),
            FStore_CountKeyUsed(&FStoreMysensor),
            reset_type,
            rf_setup,
            RF->rf_retries,
            RF->rf_channel,
            RF->rf_aw & 0b11,
            RF->rf_addr[4], RF->rf_addr[3], RF->rf_addr[2], RF->rf_addr[1], RF->rf_addr[0]
            );

    printf("Report full: [%s]\n", full_report_msg);
    send(msg_Custom.set(full_report_msg));
  }

#endif





/********************************************************************************/
void customReport() {
  char report_msg[25];

  sprintf(report_msg, "%02X%04X%04X",
          getParentNodeId(),
          millis() / 60000,   // uptime_minute
          UID
          );

  printf("Report: [%s]\n", report_msg);
  send(msg_Custom.set(report_msg));

  CUSTOMLED_TOGGLE();
}



/********************************************************************************/
void customInit() {
  if (!Watchdog_hardware_begin()) {
    //printf("WDG_HW failed\n");
    return;
  }
  //printf("WDG_HW success\n");
  Watchdog_setPrescaler(IWDG_Prescaler_32);  // see more: Watchdog.h

  customLedBlinkEnable();

  for (int i = 0; i < 5; i++) {
    hwWatchdogReset();
    delay(500);
  }


  FStore_Begin(&FStoreMysensor, MYSENSOR_START_ADDR, MYSENSOR_FSTORE_NUM_PAGE, MYSENSOR_FSTORE_ID);
  customLoadConfig();

  //customBaseReport();
  UID = Core_GetUid16();

  ResetFlags_Begin();
       if (ResetFlags_Check(RESET_FLAG_POWER))                reset_type = 0;
  else if (ResetFlags_Check(RESET_FLAG_LOW_POWER))            reset_type = 1;
  else if (ResetFlags_Check(RESET_FLAG_WATCHDOG_WINDOWN))     reset_type = 2;
  else if (ResetFlags_Check(RESET_FLAG_WATCHDOG_INDEPENDENT)) reset_type = 3;
  else if (ResetFlags_Check(RESET_FLAG_SOFTWARE))             reset_type = 4;
  else if (ResetFlags_Check(RESET_FLAG_NRST_PIN))             reset_type = 5;
}


/********************************************************************************/
void customWatchdogReset() {
  Watchdog_reset();
}

/********************************************************************************/
void customWriteByte(unsigned int offset, uint8_t data) {
  FStore_SetKey8(&FStoreMysensor, offset, data);
}

uint8_t customReadByte(unsigned int offset) {
  return FStore_GetKey8(&FStoreMysensor, offset);
}

/********************************************************************************/

void customCommands(const char *command) {
  static uint32_t last_cmd_ms = 0;

  uint32_t now_ms = millis();
  if ((now_ms - last_cmd_ms) > 500) {
    last_cmd_ms = now_ms;

    char cmd_str[3] = {command[0], command[1], '\0'};
    uint8_t cmd = strtoul(cmd_str, NULL, 16);
    const char *opt = command + 2;  // skip "cmd"

    #ifndef MY_GATEWAY_SERIAL
      printf("cmd = [%X]", cmd);
      printf(", ");
      printf("opt = [%s]", opt);
      printf("\n");
    #endif

    switch (cmd) {
      case CMD_RESTART       : hwReboot();       break;
      case CMD_LED_ON        : CUSTOMLED_HIGH(); break;
      case CMD_LED_OFF       : CUSTOMLED_LOW();  break;

      case CMD_REPORT_FULL   : customReportFull();           break;
      case CMD_REPORT        : customReport();               break;
      case CMD_RENEW_ID      : customRenewID();              break;
      case CMD_RENEW_PARENT  : customRenewParent();          break;
      case CMD_RF_TXPOWER    : customConfigRF_TxPower(opt);  break;
      case CMD_RF_TXRETRY    : customConfigRF_TxRetry(opt);  break;
      case CMD_RF2_TXPOWER   : customConfigRF2_TxPower(opt); break;
      case CMD_RF2_TXRETRY   : customConfigRF2_TxRetry(opt); break;
      case CMD_RF2_CBA       : customConfigRF2_CBA(opt);     break;
      case CMD_RF2_ACTIVE    : customConfigRF2_Active();     break;
    }
  }
}
