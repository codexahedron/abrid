/**
  \file      idt.h
  \brief     IDT support.
  \details   This header file is used for IDT support.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __IDT_H
#define __IDT_H

/** 
   \brief Sets an IDT gate.
*/
void idt_set_gate(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
/** 
   \brief Installs the IDT to the kernel.

   This function installs the Interrupt Descriptor Table (IDT) into the kernel.
*/
void idt_install();

#endif