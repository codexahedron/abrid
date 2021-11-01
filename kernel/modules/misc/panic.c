#include <screen.h>

void panic(char* reason, int errno) {
	char* buf;
	green_screen();
	putstr("---KERNEL PANIC 0x", COLOR_LBU, COLOR_GRN);
	putstr(itoa(errno, buf, 16), COLOR_LBU, COLOR_GRN);
	putstr("---\n", COLOR_LBU, COLOR_GRN);
	putstr("The reason for the kernel panic should be below.\n", COLOR_WHT, COLOR_GRN);
	putstr(reason, COLOR_LBU, COLOR_GRN);
	while(1);
}