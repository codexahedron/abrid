/**
  \file      panic.h
  \brief     Provides kernel panic ability for the kernel
  \details   Allows the kernel to kernel panic, with reasonable amounts of details and a log.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/


#ifndef __PANIC_H
#define __PANIC_H

/**
	\def INSUFFICIENT_RAM
	\brief Insufficient RAM error code
*/
#define INSUFFICIENT_RAM 1
/**
	\def UNKNOWN
	\brief Unknwon error error code
*/
#define UNKNOWN 2
/**
	\def MEMORY_MAP_INVALID
	\brief GRUB memory map is invalid

	If the GRUB memory map is invalid, something is wrong with GRUB. Please update GRUB or report an issue to our GitHub.
*/
#define MEMORY_MAP_INVALID 3
/**
	\def USER_CREATED_PANIC
	\brief Happens if the user creates a panic with the `panic` command
*/
#define USER_CREATED_PANIC 4

void panic(char* reason, int errno);
#endif