#ifndef MyCustoms_h
#define MyCustoms_h

/********************************************************************************/
#define ID_CUSTOM   (0x0A)

/********************************************************************************/
#define  CMD_RESTART                0xFF

#define  CMD_RENEW_ID               0x01
#define  CMD_RENEW_PARENT           0x02
#define  CMD_RF_TXPOWER             0x03
#define  CMD_RF_TXRETRY             0x04
#define  CMD_RF2_TXPOWER            0x05
#define  CMD_RF2_TXRETRY            0x06
#define  CMD_RF2_CBA                0x07
#define  CMD_RF2_ACTIVE             0x08
#define  CMD_LED_ON                 0x09
#define  CMD_LED_OFF                0x0A


#define  CMD_REPORT_FULL            0x00  // len = 20
#define  CMD_REPORT                 0x0B  // len = 10

/********************************************************************************/
typedef struct {
  uint8_t rf_config;     // crc mode
  uint8_t rf_aw;         // address width
  uint8_t rf_retries;    // retransmit timeout, count
  uint8_t rf_channel;    // channel frequency
  uint8_t rf_setup;      // tx power, baud
  uint8_t rf_addr[5];    // base address
} CUSTOM_CONFIG;

extern CUSTOM_CONFIG *RF;

/********************************************************************************/
void customInit();

void customLedBlinkEnable();
void customLedBlinkDisable();

void customLedOn();
void customLedOff();
void customLedToggle();

void customLoadConfig();
//void customSaveConfig();

void customRetryConfig();
void customSwitchRFActive();

void customCommands(const char *command);

void customReportFull();
void customReport();



/// Watchdog:
void customWatchdogReset();


/// FStore:
void    customWriteByte(unsigned int offset, uint8_t data);
uint8_t customReadByte(unsigned int offset);


/********************************************************************************/
#endif // MyCustoms_h
