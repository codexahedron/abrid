/**
  \file      multibootinfo.h
  \brief     Multiboot info, obtained from the kernel main function
  \details   This header file is used in files except main.c to get multiboot info.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#include <multiboot.h>

#ifndef __MULTIBOOTINFO_H
#define __MULTIBOOTINFO_H

	multiboot_info_t* mbi;

#endif