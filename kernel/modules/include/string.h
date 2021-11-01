/**
  \file      string.h
  \brief     Provides string manipulation support to the kernel
  \details   Allows the kernel to manipulate strings.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __STRING_H
#define __STRING_H

/**
	\brief Swaps 2 strings
*/
void swap(char *x, char *y);
/**
	\brief Reverses a string
	\param{in} buffer Buffer
	\param{in} i Should most of the time be 0
	\param{in} j Should most of the time be strlen(buffer);
	\returns The reversed string
*/
char* reverse(char *buffer, int i, int j);
/**
	\brief Converts an integer into a string
	\param{in} num The original number
	\param{in} str Buffer
	\param{in} base Should most of the time be 10. The base value of the number (e.g. 16 for hexadecimal).
	\returns The converted string
*/
char *itoa(int num, char* str, int base);
/**
	\brief Gets the length of a string
	\param{in} s The string
	\returns The length of s
*/
int strlen(char s[]);
/**
	\brief Compares 2 strings

	result == 0 if the contents are equal, 
	result < 0 if the first character that does not match has a lower value in s1 than in s2,
	result > 0 if the first character that does not match has a greater value in s1 than in s2.
	\param{in} s1 String #1
	\param{in} s2 String #2
	\returns The resulting number (read the description)
*/
int strcmp(char s1[], char s2[]);
/**
	\brief Concatenates 2 strings

	Destination is modified, the return value is not needed most of the time.
	\param{in} destination The string to start with
	\param{in} source The string to end with
	\returns destination after the concatenation
*/
char* strcat(char* destination, const char* source);
/**
	\brief Gets the 1st token of a string if a string is passed, or the N-st element of the previous string if NULL is passed.
	\param{in} str The string to tokenize
	\param{in} delim The delimiter to split
	\returns The first token of a string
*/
char *strtok(char* str, const char* delim);
/**
	\brief Duplicates a string

	Destination is modified, the return value is not needed most of the time.
	\param{in} destination The string to set to source
	\param{in} source The string to be copied
	\returns The value of destination, after the copying
*/
char* strcpy(char* destination, const char* source);
/**
	\brief Returns the first instance of Y in X, or NULL if Y is not found in X.
	\param{in} X The string to get the first instance of
	\param{in} Y The string that is the instance
	\returns The first instance of Y in X, or NULL
*/
const char* strstr(const char* X, const char* Y);
/**
	\brief Converts a string to a integer
	\param{in} str The string to convert
	\returns The converted integer
*/
int atoi(char* str);
/**
	\brief Octal ASCII character to decimal converter
	\param{in} n The character to convert
	\returns The resulting decimal
*/
int octtodec(int n);

// Non-standarized utility functions:

/**
	\brief Gets if a string starts with another string
	\param{in} starts The string that it may/may not start with
	\param{in} s The string to get if it starts with `starts`
	\returns 1 if it starts with `starts`, 0 otherwise
*/
int starts_with(char* starts, char* s);

#endif
