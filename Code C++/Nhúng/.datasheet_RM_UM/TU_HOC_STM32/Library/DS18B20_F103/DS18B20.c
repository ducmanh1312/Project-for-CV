
#include <stdio.h>  // for: NULL

#include "DS18B20.h"

/**********************************************************************/
/* Internal macros */
#define OW_FIRST_DEV                    0xFF
#define OW_LAST_DEV                     0x00

#define ONEWIRE_BYTE_RESET              0xF0

/**********************************************************************/
uint8_t ds18x20_start(OneWireUSART* ow, uint8_t* rom_id) {
  uint8_t ret = 0;

  if (ow_reset(ow) == true) {     // Try to reset devices
    if (rom_id == NULL) {         // Check for ROM id
      ow_skip_rom(ow);            // Skip ROM, send to all devices
    } else {
      ow_match_rom(ow, rom_id);   // Select exact device by ROM address
    }
    ow_write_byte(0x44);          // Start temperature conversion
    ret = 1;
  }

  return ret;
}


/**********************************************************************/
uint8_t ds18x20_is_b(OneWireUSART* ow, uint8_t* rom_id) {
  return rom_id != NULL && *rom_id == 0x28;   // Check for correct ROM family code
}

/**********************************************************************/
uint8_t ds18x20_is_s(OneWireUSART* ow, uint8_t* rom_id) {
  return rom_id != NULL && *rom_id == 0x10;   // Check for correct ROM family code
}


/**********************************************************************/
uint8_t ds18x20_read(OneWireUSART* ow, uint8_t* rom_id, float* t) {
  uint8_t ret = 0, data[9], i, crc, resolution, m = 0;
  int8_t digit;
  float dec;
  uint16_t temp;

  // Check ROM device
  if (rom_id != NULL && !ds18x20_is_b(ow, rom_id) && !ds18x20_is_s(ow, rom_id)) {
    return 0;
  }
  //ow_protect(ow);   /* Protect 1-Wire */

  /*
   * First read bit and check if all devices completed with conversion.
   * If everything ready, try to reset the network and continue
   */
  if (ow_read_bit(ow) && ow_reset(ow) == true) \
  {
    if (rom_id == NULL) {                             /* Check for ROM id */
      ow_skip_rom(ow);                                /* Skip ROM, send to all devices */
    } else {
      ow_match_rom(ow, rom_id);                       /* Select exact device by ROM address */
    }
    ow_write_byte(OW_CMD_RSCRATCHPAD);                /* Send command to read scratchpad */

    /* Read plain data from device */
    for (i = 0; i < 9; i++) {
      data[i] = ow_read_byte(ow);                     /* Read byte */
    }
    crc = ow_crc(data, 0x09);                         /* Calculate CRC */

    if (!crc) {                                       /* Result must be 0 to match the CRC */
      temp = data[1] << 0x08 | data[0];               /* Format data in integer format */
      resolution = ((data[4] & 0x60) >> 0x05) + 0x09; /* Set resolution in units of bits */
      if (temp & 0x8000) {                            /* Check for negative temperature */
        temp = ~temp + 1;                             /* Perform two's complement */
        m = 1;
      }
      digit = (temp >> 0x04) | (((temp >> 0x08) & 0x07) << 0x04);

      switch (resolution) {    /* Check for resolution settings */
        case 9:  dec = ((temp >> 0x03) & 0x01) *    0.5f; break;
        case 10: dec = ((temp >> 0x02) & 0x03) *   0.25f; break;
        case 11: dec = ((temp >> 0x01) & 0x07) *  0.125f; break;
        case 12: dec = ((temp >> 0x00) & 0x0F) * 0.0625f; break;
        default: dec = 0xFF, digit = 0;
      }

      dec += digit;
      if (m) {
        dec = -dec;
      }
      *t = dec;
      ret = 1;
    }
  }

  //ow_unprotect(ow);   /* Unprotect 1-Wire */
  return ret;
}

/**********************************************************************/
