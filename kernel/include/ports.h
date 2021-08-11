#ifndef __PORTS_H
#define __PORTS_H

extern unsigned char in_port_byte(unsigned short port);
extern void out_port_byte(unsigned short port, unsigned char data);
extern unsigned char inb(unsigned short port);
extern void outb(unsigned short port, unsigned char data);
#endif