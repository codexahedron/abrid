#ifndef __KSHELL_H
#define __KSHELL_H

int dfs;

void kshell_init();
void kshell(char s[], int i);
void clear_scr();
void halt();
void reboot();
void unknown_command(char s[]);
void available_commands();

#endif