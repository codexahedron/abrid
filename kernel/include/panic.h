#ifndef __PANIC_H
#define __PANIC_H

#define INSUFFICIENT_RAM 1
#define UNKNOWN 2
#define MEMORY_MAP_INVALID 3
#define USER_CREATED_PANIC 4

void panic(char* reason, int errno);
#endif