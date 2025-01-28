#ifndef MyTransportNRF24_h
#define MyTransportNRF24_h

static void transportRxCallback(void);
bool transportInit(void);
void transportSetAddress(const uint8_t address);
uint8_t transportGetAddress(void);
bool transportSend(const uint8_t to, const void* data, const uint8_t len);
bool transportAvailable(void);
bool transportSanityCheck(void);

#endif
