#ifndef __STDINT_H
#define __STDINT_H

typedef char int8_t;
typedef unsigned char uint8_t;
    
typedef short int16_t;
typedef unsigned short uint16_t;
    
typedef int int32_t;
typedef unsigned int uint32_t;
    
typedef long long int int64_t;
typedef unsigned long long int uint64_t;

typedef int8_t int_least8_t;
typedef uint8_t uint_least8_t;

typedef int16_t int_least16_t;
typedef uint16_t uint_least16_t;

typedef int32_t int_least32_t;
typedef uint32_t uint_least32_t;

typedef int64_t int_least64_t;
typedef uint64_t uint_least64_t;

typedef int8_t int_fast8_t;
typedef uint8_t uint_fast8_t;

typedef int16_t int_fast16_t;
typedef uint16_t uint_fast16_t;

typedef int32_t int_fast32_t;
typedef uint32_t uint_fast32_t;

typedef int64_t int_fast64_t;
typedef uint64_t uint_fast64_t;

typedef long int intptr_t;

typedef unsigned long int uintptr_t;

typedef long int intmax_t;
typedef unsigned long int uintmax_t;

// regular
#define INT8_MIN -128
#define INT16_MIN -32767-1
#define INT32_MIN -2147483647-1
#define INT64_MIN -9223372036854775807-1

#define INT8_MAX 127
#define INT16_MAX 32767
#define INT32_MAX 2147483647
#define INT64_MAX 9223372036854775807

#define UINT8_MAX 255
#define UINT16_MAX 65535
#define UINT32_MAX 4294967295U
#define UINT64_MAX 18446744073709551615

//least
#define INT_LEAST8_MIN -127
#define INT_LEAST16_MIN -32767
#define INT_LEAST32_MIN -2147483647
#define INT_LEAST64_MIN -9223372036854775807

#define INT_LEAST8_MAX 255
#define INT_LEAST16_MAX 65535
#define INT_LEAST32_MAX 4294967295
#define INT_LEAST64_MAX 18446744073709551615

#define UINT_LEAST8_MAX 255
#define UINT_LEAST16_MAX 65535
#define UINT_LEAST32_MAX 4294967295
#define UINT_LEAST64_MAX 18446744073709551615

// fast
#define INT_FAST8_MIN -127
#define INT_FAST16_MIN -32767
#define INT_FAST32_MIN -2147483647
#define INT_FAST64_MIN -9223372036854775807

#define INT_FAST8_MAX 255
#define INT_FAST16_MAX 65535
#define INT_FAST32_MAX 4294967295
#define INT_FAST64_MAX 18446744073709551615

#define UINT_FAST8_MAX 255
#define UINT_FAST16_MAX 65535
#define UINT_FAST32_MAX 4294967295
#define UINT_FAST64_MAX 18446744073709551615



#define INTPTR_MIN -32767
#define INTPTR_MAX 32767

#define UINTPTR_MAX 65535


#define INTMAX_MIN -9223372036854775807
#define INTMAX_MAX 9223372036854775807
#define UINTMAX_MAX 18446744073709551615

#endif
    