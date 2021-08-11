#ifndef __STRING_H
#define __STRING_H


void swap(char *x, char *y);
char* reverse(char *buffer, int i, int j);
char *itoa(int num, char* str, int base);
int strlen(char s[]);
int strcmp(char s1[], char s2[]);
char* strcat(char* destination, const char* source);
char* strtok(char *s, const char *delim);
char* strcpy(char* destination, const char* source);
const char* strstr(const char* X, const char* Y);
int atoi(char* str);
int octtodec(int n);

char *strdup(char *src);
#endif
