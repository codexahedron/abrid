/**
  \file      bigint.h
  \brief     Huge integer support.
  \details   This header file is used for big int support.
  \author    mechanikate
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __BIGINT_H
#define __BIGINT_H

/**
  \def MAX_BIGINT_GROUPS
  \brief The maximum number of groups of unsigned longs in a bigint.

  The max value of any bigint is then equal to (1 << (MAX_BIGINT_GROUPS << 5)).
*/
#define MAX_BIGINT_GROUPS 256

/**
    \struct bigint
    \brief Type for storing big ints.
    \details Consists of 3 main properties: sign, size, and digits. sign (int) should only ever be -1 or 1, where -1 means the int is negative and 1 means the int is positive. Note that zero is classified as positive. digits (uint32_t*) is an array of unsigned longs usually capped at 2^31-1, where each unsigned long is 31 bits of numbers. All of the digits are summed together when converting to long long in a way that lets you store huge values. You shouldn't need this struct generally, as to_bigint and to_int do mostly what you need, and operators like add do addition.
*/
typedef struct bigint {
    int sign;
    unsigned long digits[MAX_BIGINT_GROUPS]; // max value: 2^(MAX_BIGINT_GROUPS*32)-1
} bigint_t;

/**
    \brief Resets all digit values to 0, effectively making the number equal 0.
    \returns A zeroed-out bigint.
*/
bigint_t clear_digits();

/**
    \brief Gets number of value bits in a long long int.
    \param{in} The input long long int.
    \returns The number of bits used in the long long int.
*/
int bits(long long num);

/**
    \brief Converts a long long int to a bigint.
    \param{in} n The long long int to convert.
    \returns The bigint equivalent of the long long int.
*/
bigint_t to_bigint(long long n);

/**
    \brief Converts a bigint to a long long int.
    \param{in} n The bigint to convert.
    \returns The long long int equivalent of the bigint. Warning: this will not be accurate for values above LLONG_MAX, or 9,223,372,036,854,775,807.
*/
long long to_int(bigint_t n);

/**
    \brief Adds two bigints together.
    \param{in} a One addend.
    \param{in} b Another addend.
    \returns The sum of the two addends.
*/
bigint_t add(bigint_t a, bigint_t b);

/**
    \brief Calculates the nth Fibonacci number.
    Mostly useless/for fun, but this calculates the nth number in the Fibonacci sequence.
    \param{in} n How far to calculate.
    \returns The nth Fibonacci number in bigint form.
*/
bigint_t fib(int n);

/**
    \brief Calculates a bitwise shift on a to the left amt times.
    \param{in} a The bigint to perform the shift on.
    \param{in} amt The amount of times to shift.
    \returns The shifted bigint.
*/
bigint_t shiftleft(bigint_t a, int amt);

/**
    \brief Calculates the product of a and b.
    \param{in} a One multiplicand.
    \param{in} b Another multiplicand.
    \returns The inverted bigint.
*/
bigint_t mul(bigint_t a, bigint_t b);

/**
    \brief Calculates a bitwise NOT on a (~a).
    \param{in} a The bigint to perform the NOT operation on.
    \returns The inverted bigint.
*/
bigint_t not(bigint_t a);

/**
    \brief Calculates -1*a, or -a.
    \param{in} a The bigint to negate.
    \returns The negated bigint.
*/
bigint_t flip(bigint_t a);

/**
    \brief Calculates a-b.
    \param{in} a The minuend.
    \param{in} b The subtrahend.
    \returns The difference of a and b.
*/
bigint_t sub(bigint_t a, bigint_t b);

/**
    \brief Calculates if x>y.
    If x>y, return 1. If x<y, return -1. If x==y, return 0.
    \param{in} n How far to calculate.
    \returns The nth Fibonacci number in bigint form.
*/
int greater_than(bigint_t x, bigint_t y);

/**
    \brief Calculates if x<y.
    If x<y, return 1. If x>y, return -1. If x==y, return 0.
    \param{in} x The first parameter in the inequality.
    \param{in} y The second parameter in the inequality.
    \returns The nth Fibonacci number in bigint form.
*/
int less_than(bigint_t x, bigint_t y);

#endif