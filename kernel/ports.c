#include <ports.h>

unsigned char in_port_byte(unsigned short port){
    unsigned char result;
    __asm__ volatile("in %%dx, %%al": "=a"(result) : "d" (port));

    return result;
}

void out_port_byte(unsigned short port, unsigned char data){
	__asm__ volatile("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned char inb(unsigned short port){
	return in_port_byte(port);
}
void outb(unsigned short port, unsigned char data){
	outb(port, data);
}