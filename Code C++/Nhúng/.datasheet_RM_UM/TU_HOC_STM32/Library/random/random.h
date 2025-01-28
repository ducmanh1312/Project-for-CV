#ifndef __RANDOM_H__
#define __RANDOM_H__

#include "basic.h"
C_DECLS_BEGIN

/**********************************************************************/
void     Rand_begin(uint32_t seed);

uint8_t  Rand_get8();
uint16_t Rand_get12();
uint16_t Rand_get16();
uint32_t Rand_get32();

/**********************************************************************/
C_DECLS_END
#endif // __RANDOM_H__

