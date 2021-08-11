#ifndef __SHELL_H
#define __SHELL_H

#include <fs.h>

#define NULL ((char *)0)
#define sizeof(type) (char *)(&type+1)-(char*)(&type)

extern int enable_shell;

fs_node_t blank;

void shell_init();

void shell(char s[], int i);

#endif