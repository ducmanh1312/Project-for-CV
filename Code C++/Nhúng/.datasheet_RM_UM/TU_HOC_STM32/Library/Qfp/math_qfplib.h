#ifndef __MATHQFPLIB_H__
#define __MATHQFPLIB_H__


#include "basic.h"
C_DECLS_BEGIN

/**********************************************************************/
#include "qfplib-common.h"

#ifdef STM32F10X_MD
  #include "qfplib-m3.h"
#endif

#ifdef STM32F0XX
  #include "qfplib.h"
#endif


/**********************************************************************/
/// basic:
/**********************************************************************/
ATTRIBUTE_USED
float __aeabi_fadd(float x, float y) {
  return qfp_fadd(x, y);
}

ATTRIBUTE_USED
float __aeabi_fsub(float x, float y) {
  return qfp_fsub(x, y);
}

ATTRIBUTE_USED
float __aeabi_fmul(float x, float y) {
  return qfp_fmul(x, y);
}

ATTRIBUTE_USED
float __aeabi_fdiv(float x, float y) {
  return qfp_fdiv(x, y);
}


/**********************************************************************/
/// conversions:
/**********************************************************************/
ATTRIBUTE_USED
int __aeabi_f2iz(float x) {
	return qfp_float2int(x);
}

ATTRIBUTE_USED
float __aeabi_i2f(int x) {
	return qfp_int2float(x);
}

ATTRIBUTE_USED
unsigned int __aeabi_f2uiz(float x) {
	return qfp_float2uint(x);
}

ATTRIBUTE_USED
float __aeabi_ui2f(unsigned int x) {
	return qfp_uint2float(x);
}


/**********************************************************************/
/// comparison:
/**********************************************************************/
ATTRIBUTE_USED
int __aeabi_fcmpgt(float x, float y) {
	return (qfp_fcmp(x, y) > 0);
}

ATTRIBUTE_USED
int __aeabi_fcmplt(float x, float y) {
  return (qfp_fcmp(x, y) < 0);
}

ATTRIBUTE_USED
int __aeabi_fcmpeq(float x, float y) {
  return (qfp_fcmp(x, y) == 0);
}


/**********************************************************************/
/// scientific:
/**********************************************************************/
ATTRIBUTE_USED
float sinf(float x) {
  return qfp_fsin(x);
}

ATTRIBUTE_USED
float cosf(float x) {
  return qfp_fcos(x);
}

ATTRIBUTE_USED
float tanf(float x) {
  return qfp_ftan(x);
}

ATTRIBUTE_USED
float atan2f(float y, float x) {
  return qfp_fatan2(y, x);
}

ATTRIBUTE_USED
float expf(float x) {
  return qfp_fexp(x);
}

ATTRIBUTE_USED
float logf(float x) {
  return qfp_fln(x);
}

ATTRIBUTE_USED
float sqrtf(float x) {
  return qfp_fsqrt(x);
}

/**********************************************************************/
C_DECLS_END
#endif  // __MATHQFPLIB_H__
