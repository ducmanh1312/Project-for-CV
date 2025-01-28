#ifndef __ONEWIREUSART_H__
#define __ONEWIREUSART_H__


/**********************************************************************/
#include "basic.h"
C_DECLS_BEGIN


/**********************************************************************/
#define OW_UNUSED(x)                ((void)(x))

#define OW_CMD_RSCRATCHPAD          0xBE
#define OW_CMD_WSCRATCHPAD          0x4E
#define OW_CMD_CPYSCRATCHPAD        0x48
#define OW_CMD_RECEEPROM            0xB8
#define OW_CMD_RPWRSUPPLY           0xB4
#define OW_CMD_SEARCHROM            0xF0
#define OW_CMD_READROM              0x33
#define OW_CMD_MATCHROM             0x55
#define OW_CMD_SKIPROM              0xCC


/**********************************************************************/
/**
 * \brief           1-Wire structure
 */
typedef struct {
  uint8_t rom[8];    /*!< ROM address of last device found.
                          When searching for new devices, we always need last found address,
                          to be able to decide which way to go next time during scan. */
  uint8_t disrepancy;   /*!< Disrepancy value on last search */
} OneWireUSART;


#define OW_UNUSED(x)     ((void)(x))


/**********************************************************************/
bool     ow_init();
bool     ow_reset();

uint8_t  ow_write_byte(uint8_t b);
uint8_t  ow_read_byte();

uint8_t  ow_read_bit();

bool     ow_search_reset();
bool     ow_search(OneWireUSART* ow, uint8_t *rom_id);

uint8_t  ow_match_rom(OneWireUSART* ow, uint8_t* rom_id);
uint8_t  ow_skip_rom(OneWireUSART* ow);
uint8_t  ow_crc(const void *in, int len);


/**********************************************************************/
C_DECLS_END
#endif // __ONEWIREUSART_H__
