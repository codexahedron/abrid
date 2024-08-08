#include <bigint.h>
#include <stdio.h>

bigint_t clear_digits(bigint_t modding) {
    modding.size=1;
    modding.sign=1;
    for(int i=0; i<32*MAX_BIGINT_GROUPS; i+=32) {
        modding.digits[i/32] = 0;
    }
    return modding;
}
int bits(long long num) {
    int retVal = 0;
    long long num2 = num;
    while (num2) {
        retVal++;
        num2 >>= 1;
    }
    return retVal;
}
bigint_t to_bigint(long long n) {
    bigint_t result;
    result = clear_digits(result);
    if(n>=0) { result.sign = 1; } else { result.sign = -1; }
    result.size = (bits(n) >> 5)+1;
    for(int i=0; i<result.size; i+=32) {
        result.digits[i/32] = n >> i;
    }
    return result;
}
long long to_int(bigint_t n) {
  long long result = 0;
  for(int i=32*2; i>=0; i-=32) { // not using the full 32*MAX_BIGINT_GROUPS bits because longlong can't support 2^63 or higher
    result <<= 33;
    result += n.digits[i/32];
  }
  result *= n.sign;
  return result;
}
bigint_t add(bigint_t a, bigint_t b) {
    bigint_t result;
    result.sign = a.sign * b.sign;
    result.size = a.size > b.size ? a.size : b.size;
    result = clear_digits(result);
    for(int i=0; i<32*MAX_BIGINT_GROUPS; i+=32) {
        if((((unsigned long) a.digits[i/32])+((unsigned long) b.digits[i/32]))>>32) { b.digits[i/32+1]++; }
        result.digits[i/32] = (a.digits[i/32] + b.digits[i/32]);
        if(result.digits[i/32] > (1LL<<32LL)) result.digits[i/32] %= 1LL<<32LL;
    }
    return result;
}
bigint_t fib(int n) {
    bigint_t a = to_bigint(0);
    bigint_t b = to_bigint(1);
    bigint_t next = add(a,b);
    for(int i=2; i<n; i++) {
        a = b;
        b = next;
        next = clear_digits(next);
        next = add(a,b);
    }
    return next;
}
void binprintf(int v) {
    unsigned int mask=1<<((sizeof(int)<<3)-1);
    while(mask) {
        printf("%d", (v&mask ? 1 : 0));
        mask >>= 1;
    }
}
void bigprintf(bigint_t z) {
    for(int i=255; i>-1; i--) {
        int v = z.digits[i];
        if(v==0) continue;
        binprintf(v);
    }

}