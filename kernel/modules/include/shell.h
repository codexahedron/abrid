/**
  \file      shell.h
  \brief     Provides shell support to the kernel
  \details   Allows the kernel to accept user input and parse it.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __SHELL_H
#define __SHELL_H

#include <fs.h>

#define NULL ((char *)0)
#define sizeof(type) (char *)(&type+1)-(char*)(&type)

extern int enable_shell;

fs_node_t blank;

/**
	\brief Initializes the shell
*/
void shell_init();

/**
	\brief Runs the shell
	\param{in} s User input to be parsed
	\param{in} i Cursor X position
*/
void shell(char s[], int i);

#endif