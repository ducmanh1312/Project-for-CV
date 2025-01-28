#ifndef __RF24_SPI_GPIO_H__
#define __RF24_SPI_GPIO_H__

#include "basic.h"
C_DECLS_BEGIN

/**********************************************************************/
void RF24_SPI_GPIO_begin();
void RF24_IRQ_begin();

uint8_t RF24_SPI_transfer(uint8_t data);

void RF24_ce(bool level);
void RF24_csn(bool level);
void RF24_wait_tx_complete();


void RF24_enableIRQ();
void RF24_disableIRQ();

void RF24_transferBegin();
void RF24_transferEnd();

/**********************************************************************/
C_DECLS_END
#endif // __RF24_SPI_GPIO_H__
