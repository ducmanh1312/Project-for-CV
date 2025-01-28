
#include <string.h>  // memcpy

#include "Core.h"
#include "OneWireUSART.h"

/**********************************************************************/
// Internal macros
#define OW_FIRST_DEV                    0xFF
#define OW_LAST_DEV                     0x00
#define ONEWIRE_BYTE_RESET              0xF0


/**********************************************************************/
#define DMA1_CH7_ENABLE()    (DMA1_Channel7->CCR |=  DMA_CCR7_EN)
#define DMA1_CH7_DISABLE()   (DMA1_Channel7->CCR &= ~DMA_CCR7_EN)

#define DMA1_CH6_ENABLE()    (DMA1_Channel6->CCR |=  DMA_CCR6_EN)
#define DMA1_CH6_DISABLE()   (DMA1_Channel6->CCR &= ~DMA_CCR6_EN)

void USART2_transfer(uint8_t *txbuf, uint8_t *rxbuf, int len) {
  // clear all DMA flag
//  DMA1->IFCR = 0xFFFFFFFF;

  // USART2 Tx, Rx request DMA enable
  USART2->CR3 = USART_CR3_DMAT | USART_CR3_DMAR;

  DMA1_Channel7->CMAR  = (uint32_t)(txbuf);
  DMA1_Channel6->CMAR  = (uint32_t)(rxbuf);

  DMA1_Channel7->CNDTR = len;
  DMA1_Channel6->CNDTR = len;

  DMA1_CH6_ENABLE();  // ready Rx
  DMA1_CH7_ENABLE();  // start Tx

  while (DMA1_Channel6->CNDTR != 0); // wait Rx complete: counter = 0
//while ((DMA1->ISR & DMA_ISR_TCIF6) == 0);  // wait flag complete

  DMA1_CH7_DISABLE();
  DMA1_CH6_DISABLE();

  USART2->CR3 = 0;    // USART2 Tx, Rx request DMA disable
}

/**********************************************************************/
void ow_transfer(uint8_t *txbuf, uint8_t *rxbuf, int len) {
  USART2_transfer(txbuf, rxbuf, len);
}


/**********************************************************************/
#define USART2_DIV_SAMPLING(__BAUD__)  (((36 * 1e6) + ((__BAUD__)/2U)) / (__BAUD__))

void ow_set_baudrate(int baud) {
  BITMASK_CLEAR(USART2->CR1, USART_CR1_UE);   // disable USART2
  USART2->BRR = USART2_DIV_SAMPLING(baud);
  BITMASK_SET(USART2->CR1, USART_CR1_UE);     // enable USART2
}


/**********************************************************************/
uint8_t ow_sen_bit(uint8_t b) {
  uint8_t r;

  /*
   * Sending logical 1 over 1-wire, send 0xFF over UART
   * Sending logical 0 over 1-wire, send 0x00 over UART
   */
  b = b ? 0xFF : 0x00;    // Convert to 0 or 1

  ow_transfer(&b, &r, 1);

  return (r == 0xFF) ? 1 : 0;  // To read bit 1, check of 0xFF sequence
}

/**********************************************************************/
uint8_t ow_read_bit() {
  return ow_sen_bit(1);   /* Send bit as `1` and read the response */
}

/**********************************************************************/
uint8_t ow_write_byte(uint8_t b) {
  uint8_t r = 0, tr[8];

  // Create output data
  for (int i = 0; i < 8; i++)	{
    //tr[i] = (b & (1 << i)) ? 0xFF : 0x00;
		tr[i] = (b & 0x01) ? 0xFF : 0x00;
		b >>= 1;
	}

  /*
   * Exchange data on UART level,
   * send single byte for each bit = 8 bytes
   */
  ow_transfer(tr, tr, 8); /* Exchange data over UART */

  /*
   * Check received data. If we read 0xFF,
   * our logical write 1 was successful, otherwise it was 0.
   */
  for (int i = 0; i < 8; i++) 	{
		//if (tr[i] == 0xFF)
		//	r |= 0x01 << i;
		r >>= 1;
	  r |= (tr[i] == 0xFF) ? 0x80 : 0x00;
  }
  return r;
}


/**********************************************************************/
uint8_t ow_read_byte(OneWireUSART* ow) {
  /*
   * When we want to read byte over 1-Wire,
   * we have to send all bits as 1 and check if slave pulls line down.
   *
   * According to slave reactions, we can later construct received bytes
   */
  return ow_write_byte(0xFF);
}


/**********************************************************************/
bool ow_search_reset(OneWireUSART* ow) {
  ow->disrepancy = OW_FIRST_DEV;   // Reset disrepancy to default value
  return true;
}

/**********************************************************************/
bool ow_reset() {
  uint8_t b = ONEWIRE_BYTE_RESET;   // Set reset sequence byte = 0xF0
  ow_set_baudrate(9600);            // Set low baudrate
  ow_transfer(&b, &b, 1);           // Exchange data over onewire
  ow_set_baudrate(115200);          // Go back to high baudrate

  // Check if any device acknowledged our pulse
  if ( (b == 0x00) || (b == ONEWIRE_BYTE_RESET) )
    return false;

  return true;
}


/**********************************************************************/
bool ow_search(OneWireUSART* ow, uint8_t *rom_id) {
  uint8_t id_bit_number, j, next_disrepancy;
  uint8_t b, b_cpl;
  //owr_t res;
  uint8_t* id = ow->rom;

  /*
   * Check for last device
   */
  if (ow->disrepancy == 0) {
    ow_search_reset(ow);
    return false;  /* No devices anymore */
  }


  /*
   * Step 1: Reset all devices on 1-Wire line to be able to listen for new command
   */
  if ( !ow_reset() )
    return false;


  /*
   * Step 2: Send search rom command for all devices on 1-Wire
   */
  ow_write_byte(OW_CMD_SEARCHROM);   /* Start with search ROM command */
  next_disrepancy = OW_LAST_DEV;     /* This is currently last device */

  id_bit_number = 64;      /* We have to read 8 bytes, each 8 bits */
  while (id_bit_number) {
    j = 8;

    while (j--) {
      b     = ow_sen_bit(1);  /* Read first bit = next address bit */
      b_cpl = ow_sen_bit(1);  /* Read second bit = complementary bit of next address bit */

      if (b && b_cpl) {
        return false;   /* We do not have device connected */
      }
      else if (!b && !b_cpl) {
        if (id_bit_number < ow->disrepancy || ((*id & 0x01) && ow->disrepancy != id_bit_number)) {
          b = 1;
          next_disrepancy = id_bit_number;
        }
      }

      ow_sen_bit(b);

      *id = (*id >> 0x01) | (b << 0x07);  // Shift ROM byte down and add next, protocol is LSB first
      id_bit_number--;
    }

    id++;  /* Go to next byte */
  }

  ow->disrepancy = next_disrepancy;           /* Save disrepancy value */
  memcpy(rom_id, ow->rom, sizeof(ow->rom));   /* Copy ROM to user memory */
  return id_bit_number == 0 ? true : false;   /* Return search result status */
}


/**********************************************************************/
void UART2_Init_A2A3() {
  // enable peripheral clock
  RCC->APB2ENR |= RCC_APB2ENR_IOPAEN;
  RCC->APB1ENR |= RCC_APB1ENR_USART2EN;

  // CTS/PA0, RTS/PA1, TX/PA2, RX/PA3, CK/PA4
  USART_InitTypeDef USART_InitStructure;
  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART2, &USART_InitStructure);       // Configure the USART2

  // Tx_A2, Rx_A3
  F103_GPIO_pinMode_output(GPIOA, 2, GPIO_Mode_AF_OD | GPIO_Speed_10MHz);
  F103_GPIO_pinMode_input(GPIOA, 3, GPIO_Mode_IPU);

  BITMASK_SET(USART2->CR1, USART_CR1_UE);   /// enable USART2
}


/***************************************************************/
void DMA1_UART2_Tx_config() { // CH7
  DMA_InitTypeDef DMA_InitStructure;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);
  DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralDST;  // Memory to peripheral
  DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;
  DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel7, &DMA_InitStructure);
}


/***************************************************************/
void DMA1_UART2_Rx_config() { // CH6
  DMA_InitTypeDef DMA_InitStructure;
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)(&USART2->DR);
  DMA_InitStructure.DMA_DIR                = DMA_DIR_PeripheralSRC;  // peripheral to memory
  DMA_InitStructure.DMA_PeripheralInc      = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc          = DMA_MemoryInc_Enable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_Byte;
  DMA_InitStructure.DMA_MemoryDataSize     = DMA_MemoryDataSize_Byte;
  DMA_InitStructure.DMA_Mode               = DMA_Mode_Normal;  // DMA_Mode_Circular
  DMA_InitStructure.DMA_Priority           = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M                = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel6, &DMA_InitStructure);
}


/**********************************************************************/
bool ow_init() {
  UART2_Init_A2A3();
  DMA1_UART2_Tx_config();
  DMA1_UART2_Rx_config();
  return true;
}


/**********************************************************************/
uint8_t ow_match_rom(OneWireUSART* ow, uint8_t* rom_id) {
  ow_write_byte(OW_CMD_MATCHROM);   /* Write byte to match rom exactly */

  /*
   * Send 8 bytes representing ROM address
   */
  for (int i = 0; i < 8; i++) {
    ow_write_byte(rom_id[i]);    /* Send ROM bytes */
  }
  return 1;
}


/**********************************************************************/
uint8_t ow_skip_rom(OneWireUSART* ow) {
  ow_write_byte(OW_CMD_SKIPROM);   /* Write byte to match rom exactly */
  return 1;
}


/**********************************************************************/
uint8_t ow_crc(const void *in, int len) {
  uint8_t crc = 0, inbyte, i, mix;
  const uint8_t* d = in;

  while (len--) {
    inbyte = *d++;
    for (i = 8; i; i--) {
      mix = (crc ^ inbyte) & 0x01;
      crc >>= 1;

      if (mix) {
        crc ^= 0x8C;
      }
      inbyte >>= 0x01;
    }
  }
  return crc;
}

/**********************************************************************/
