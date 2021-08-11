#ifndef __MEM_H
#define __MEM_H

int ram_size();

typedef unsigned long uintptr_t;
typedef long intptr_t;

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
unsigned char *memset(unsigned char *dest, unsigned char val, int count);
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
int memcmp(const void *s1, const void *s2, int len);

void *sbrk(intptr_t incr);

void malloc_init();

void free(void *firstbyte);
void *malloc(long numbytes);

#endif