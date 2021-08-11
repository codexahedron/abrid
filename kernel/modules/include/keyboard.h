#ifndef __KEYBOARD_H
#define __KEYBOARD_H 

unsigned char ascii_values[128];

char *inbuf;
char *buffer;

char get_key();

void keyboard_install();
void track_input(char c);

#endif