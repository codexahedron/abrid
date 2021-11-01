/**
  \file      gdt.h
  \brief     GDT support.
  \details   This header file is used for GDT support.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __GDT_H
#define __GDT_H
/** 
   \brief Sets an GDT gate.
*/
void gdt_set_gate(int num, unsigned long base, unsigned long limit, unsigned char access, unsigned char gran);
/** 
   \brief Installs the GDT to the kernel.

   This function installs the Global Descriptor Table (GDT) into the kernel.
*/
void gdt_install();
#endif