#include <bigint.h>
#include <stdio.h>

bigint_t clear_digits() {
    bigint_t modding;
    modding.sign=1;
    for(int i=0; i<32*256; i+=32) {
        modding.digits[i/32] = 0;
    }
    return modding;
}

int bits(long long num) {
    int retVal = 0;
    long long num2 = num;
    while (num2 != 0 && num2 != -1) {
        retVal++;
        num2 >>= 1;
    }
    return retVal;
}
bigint_t to_bigint(long long n) {
    bigint_t result = clear_digits();
    if(n>=0) { result.sign = 1; } else { result.sign = -1; }
    for(int i=0; i<MAX_BIGINT_GROUPS; i+=32) {
        result.digits[i/32] = n*result.sign >> i;
    }
    return result;
}
long long to_int(bigint_t n) {
  long long result = 0;
  for(int i=32*2; i>=0; i-=32) { // not using the full 32*256 bits because longlong can't support 2^63 or higher
    result <<= 33;
    result += n.digits[i/32];
  }
  result *= n.sign;
  return result;
}
bigint_t add(bigint_t a, bigint_t b) {
    bigint_t result = clear_digits();
    result.sign = -get_greater(a,b);
    for(int i=0; i<MAX_BIGINT_GROUPS; i++) {
        if((((unsigned long) a.digits[i])+((unsigned long) b.digits[i]))>>32) { b.digits[i+1]++; }
        result.digits[i] = (a.digits[i] + b.digits[i]);
        if(result.digits[i] > (1LL<<32LL)) result.digits[i] %= 1LL<<32LL;
    }
    return result;
}
bigint_t shiftleft32(bigint_t a) {
    bigint_t result = clear_digits();
    for(int i=1; i<MAX_BIGINT_GROUPS; i++) result.digits[i] = a.digits[i-1];
    return result;
}
bigint_t shiftleft1(bigint_t a) {
    bigint_t result = a;
    for(int i=MAX_BIGINT_GROUPS-1; i>0; i--) {
        result.digits[i-1] <<= 1;
        result.digits[i] |= result.digits[i-1] >> 32;

        result.digits[i-1] = (unsigned long) ((unsigned int) result.digits[i-1]);
    }
    return result;
}
bigint_t shiftleft(bigint_t a, int amt) {
    bigint_t result = a;
    int flag = 0;
    int n = amt % 32;
    int m = (amt - (amt % 32))/32; // equivalent to floor(amt/32) for getting number of shiftleft32's we have to do
    for(int i=0; i<m; i++) result = shiftleft32(result);
    for(int i=0; i<n; i++) result = shiftleft1(result);
    return result;
}
bigint_t mul(bigint_t a, bigint_t b) {
    bigint_t result = clear_digits();
    result.sign = a.sign*b.sign;
    for(int i=0; i<MAX_BIGINT_GROUPS; i++) {
        for(int j=0LL; j<32LL; j++) {
            if((int)(((a.digits[i])>>(j))) & 1) result = add(result, shiftleft(b, i*32+j));
        }
    }
    return result;
}
bigint_t not(bigint_t a) {
    bigint_t result = clear_digits();
    for(int i=0; i<MAX_BIGINT_GROUPS; i++) { 
        result.digits[i] = (unsigned long)(~(unsigned int)a.digits[i]);
    }
    return result;
}
bigint_t flip(bigint_t a) {
    bigint_t result = a;
    result.sign *= -1;
    return result;
}
bigint_t sub(bigint_t a, bigint_t b) {
    if(a.sign == b.sign) return add(a,b);
    if(b.sign == -1) return add(a,flip(b));
    bigint_t c = add(not(b),to_bigint(1));
    bigint_t result = add(a,c);
    result.sign = get_greater(a,c);
    return add(not(result),to_bigint(1));
}
int get_larger_magnitude(bigint_t a, bigint_t b) {
    for(int i=MAX_BIGINT_GROUPS; i>=0; i--) {
        if(a.digits[i]>b.digits[i]) return -1;
        if(a.digits[i]<b.digits[i]) return 1;
    }
    return 1;
}
int get_greater(bigint_t a, bigint_t b) {
    if(a.sign>b.sign) return -1;
    if(a.sign<b.sign) return 1;
    int res_larger_magnitude = get_larger_magnitude(a,b);
    int larger_magnitude = res_larger_magnitude != -1 ? res_larger_magnitude : 1;
    return a.sign * larger_magnitude;
}
int greater_than(bigint x, bigint y) {
    if(x.sign>y.sign) return 0;
    if(x.sign<y.sign) return 1;
    int res_larger_magnitude = get_larger_magnitude(x,y);
    return x.sign * res_larger_magnitude != -1 ? res_larger_magnitude : 2;
}
int less_than(bigint x, bigint y) {
    return greater_than(y,x);
}
bigint_t fib(int n) {
    bigint_t a = to_bigint(0);
    bigint_t b = to_bigint(1);
    bigint_t next = add(a,b);
    for(int i=2; i<n; i++) {
        a = b;
        b = next;
        next = clear_digits();
        next = add(a,b);
    }
    return next;
}