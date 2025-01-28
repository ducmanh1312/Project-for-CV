#ifndef __DS18B20_H__
#define __DS18B20_H__


/**********************************************************************/
#include "basic.h"
#include "OneWireUSART.h"  // for: OneWireUSART

C_DECLS_BEGIN

/**********************************************************************/
uint8_t ds18x20_start(OneWireUSART* ow, uint8_t* rom_id);
uint8_t ds18x20_read(OneWireUSART* ow, uint8_t* rom_id, float* t);
uint8_t ds18x20_is_b(OneWireUSART* ow, uint8_t* rom_id);
uint8_t ds18x20_is_s(OneWireUSART* ow, uint8_t* rom_id);

/**********************************************************************/
C_DECLS_END

#endif // __DS18B20_H__
