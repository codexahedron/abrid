/**
  \file      ports.h
  \brief     Provides inb/outb/etc. support for the kernel, generally ports
  \details   Allows the kernel to inportbyte, outportbyte and similar.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __PORTS_H
#define __PORTS_H

#include <types.h>

/**
	\brief In port byte function for ports

	Executes an in port byte call in inline assembly (`inb`).
*/
extern unsigned char in_port_byte(unsigned short port);
/**
	\brief Out port byte function for ports

	Executes an out port byte call in inline assembly (`outb`).
*/
extern void out_port_byte(unsigned short port, unsigned char data);

/**
	\brief In port word function for ports

	Executes an in port word call in inline assembly (`inw`).
*/
extern uint16_t inw(uint16_t port);
/**
	\brief Out port word function for ports

	Executes an out port word call in inline assembly (`outw`).
*/
extern void outw(uint16_t port, uint16_t val);

/**
	\brief In port long function for ports

	Executes an in port long call in inline assembly (`inl`).
*/
extern uint32_t inl(uint16_t port);
/**
	\brief Out port long function for ports

	Executes an out port long call in inline assembly (`outl`).
*/
extern void outl(uint16_t port, uint32_t val);

#endif