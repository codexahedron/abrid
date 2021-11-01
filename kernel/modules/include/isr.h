/**
  \file      isr.h
  \brief     ISR support.
  \details   This header file is used for interrupt service routine support.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __ISR_H
#define __ISR_H

/**
  \brief     Installs the ISR support into the kernel.
*/
void isr_install();
/**
  	\struct initrd_file_header_t
  	\brief Initrd file header typedef struct
  
  	Initial ramdisk file header type.
  	The following is a data structure that defines how stack looks when an ISR is running.
	As we know, we push the pointer of stack on to the stack when an ISR occurs, to handle those interrupts using our C fault handler we use the following to show how stack looks like.

  	This struct consists of:
		gs, fs, es, ds: Pushed the segs last
		edi, esi, ebp, esp, ebx, edx, ecx, eax: Pushed by pusha
		int_no, err_ciode: Our "push byte #" and ecodes do this
		eip, cs, eflags, useresp, ss: Pushed by the processor automatically
*/
struct regs
{
    unsigned int gs, fs, es, ds;      /* pushed the segs last */
    unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
    unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
    unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
};

#endif