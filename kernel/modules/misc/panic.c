#include <screen.h>

void panic(char* reason, int errno) {
	char* buf;
	putstr("---KERNEL PANIC 0x", COLOR_RED, COLOR_BLK);
	putstr(itoa(errno, buf, 16), COLOR_LRD, COLOR_BLK);
	putstr("---\n", COLOR_RED, COLOR_BLK);
	putstr("The reason for the kernel panic should be below.\n", COLOR_WHT, COLOR_BLK);
	putstr(reason, COLOR_LRD, COLOR_BLK);
	while(1);
}