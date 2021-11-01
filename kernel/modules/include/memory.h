/**
  \file      memory.h
  \brief     Memory support.
  \details   This header file is used for memory allocation/freeing/etc. support.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __MEM_H
#define __MEM_H

/**
	\brief Gets RAM installed

	Gets the amount of RAM installed in the computer.
*/
int ram_size();

/**
  \typedef unsigned long uintptr_t
  \brief Defines a unsigned long for uintptr_t
*/
typedef unsigned long uintptr_t;
/**
  \typedef long intptr_t
  \brief Defines a long for intptr_t
*/
typedef long intptr_t;

/**
  \brief Copies first `count` bytes of data from src to dest
*/
unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count);
/**
  \brief Sets first `count` bytes of data from val to dest
*/
unsigned char *memset(unsigned char *dest, unsigned char val, int count);
/**
  \brief Same as memset, but with short*s instead of char*s
*/
unsigned short *memsetw(unsigned short *dest, unsigned short val, int count);
/**
  \brief Compares first `len` bytes of data of s1 and s2
*/
int memcmp(const void *s1, const void *s2, int len);

// unused, I think
void *sbrk(intptr_t incr);

/**
  \brief Initializes malloc function
*/
void malloc_init();

/**
  \brief Frees the memory of *firstbyte
*/
void free(void *firstbyte);
/**
  \brief Allocates memory with the size being numbytes
*/
void *malloc(long numbytes);

#endif