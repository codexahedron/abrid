/**
  \file      keyboard.h
  \brief     Keyboard support.
  \details   This header file is used for keyboard support.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __KEYBOARD_H
#define __KEYBOARD_H 

unsigned char ascii_values[128];

char *inbuf;
char *buffer;

// unused
char get_key();

/**
	\brief Installs a keyboard handler

	Installs a keyboard handler.
*/
void keyboard_install();
/**
	\brief Tracks the input of the keyboard

	Tracks the input of the keyboard, to be passed to kshell.
	\param{in} c The character to be checked and possibly added to the input
*/
void track_input(char c);

#endif