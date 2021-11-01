/**
  \file      screen.h
  \brief     Provides screen output to the kernel
  \details   Allows the kernel to printf, kprintf, etc.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef __SCREEN_H
#define __SCREEN_H

/**
	\def VGA_START
	\brief VGA start address
*/
#define VGA_START 0xb8000 //VGA start address
/**
	\def VGA_WIDTH
	\brief VGA width
*/
#define VGA_WIDTH 80 //these are max coloumns in VGA
/**
	\def VGA_HEIGHT
	\brief VGA height
*/
#define VGA_HEIGHT 25 //these are max rows in VGA
/**
	\def VGA_EXTENT
	\brief VGA extent
*/
#define VGA_EXTENT 80*25

//defining available colors
#define COLOR_BLK 0     // Black
#define COLOR_BLU 1     // Blue
#define COLOR_GRN 2     // Green
#define COLOR_CYN 3     // Cyan
#define COLOR_RED 4     // Red
#define COLOR_PRP 5     // Purple
#define COLOR_BRN 6     // Brown
#define COLOR_GRY 7     // Gray
#define COLOR_DGY 8     // Dark Gray
#define COLOR_LBU 9     // Light Blue
#define COLOR_LGR 10    // Light Green
#define COLOR_LCY 11    // Light Cyan
#define COLOR_LRD 12    // Light Red
#define COLOR_LPP 13    // Light Purple
#define COLOR_YEL 14    // Yellow
#define COLOR_WHT 15    // White


//I/O ports which map the screen cursor position can be queried
//from port 0x3d4 with value 14 to request the cursor position high byte
//and we also query the same port with value 15 in the low byte
//when this port is queried, the result is saved in 0x3d5

//cursor ports:
//command port = 0x3d4 query the cursor position here
//data port = 0x3d5 read from here
/**
	\def CURSOR_PORT_COMMAND
	\brief 0x3d4 Query the cursor position here
*/
#define CURSOR_PORT_COMMAND (unsigned short) 0x3d4
/**
	\def CURSOR_PORT_DATA
	\brief 0x3d5 Read from here
*/
#define CURSOR_PORT_DATA (unsigned short) 0x3d5

/**
  \struct fs_node
  \brief VGA char typedef struct

  Defines a single character struct with close packing.
  This struct consists of:
  I. char: The character of the vga_char
  II. style: The color/style of the vga_char
*/
typedef struct __attribute__((packed)){
	char character;
	char style;
} vga_char;

/**
	\brief Applies foreground and background colors to the character
	\param{in} fg_color Foreground color
	\param{in} bg_color Background color
*/
unsigned char vga_color(const unsigned char fg_color, const unsigned char bg_color);

/**
	\brief Clears the window or screen with a color replacement
	\param{in} fg_color Foreground color
	\param{in} bg_color Background color
*/
void clear(const unsigned char fg_color, const unsigned char bg_color);

/**
	\brief Prints a character to the screen
	\param{in} character The character to print
	\param{in} fg_color Foreground color
	\param{in} bg_color Background color
*/
void putchar(const char character, const unsigned char fg_color, const unsigned char bg_color);

/**
	\brief Prints a string to the screen
	\param{in} string The string to print
	\param{in} fg_color Foreground color
	\param{in} bg_color Background color
*/
void putstr(const char *string, const unsigned char fg_color, const unsigned char bg_color);

/**
	\brief Gets the cursor position
*/
unsigned short get_cursor_pos();

/**
	\brief Shows the cursor
*/
void show_cursor();
/**
	\brief Hides the cursor
*/
void hide_cursor();

/**
	\brief Advances the cursor
*/
void advance_cursor();
/**
	\brief Moves the cursor back
*/
void move_back_cursor();
/**
	\brief Sets the cursor position
	\param{in} x X coordinate of the cursor position to set
	\param{in} y Y coordinate of the cursor position to set
*/
void set_cursor_pos(unsigned char x, unsigned char y);

/**
	\brief Prints a character

	Prints a character with the foreground being white and the background being black.
	\param{in} ch Character to print
*/
void kprintc(const char *ch);
/**
	\brief Prints a string

	Prints a string with the foreground being white and the background being black.
	\param{in} string String to print
*/
void kprintf(const char *string);
/**
	\brief Prints a string with formatting

	Prints a string with the foreground being white and the background being black, and with formatting. This formatting allows for adding things like %s, %x, and %d.
	\param{in} string String to print, with formatting
*/
void printf(char *format, ...);

/**
	\brief Puts a character at a position

	Puts a character at position (x,y) with the foreground being forecolour and the background being backcolour.
	\param{in} c Character to print
	\param{in} forecolour Foreground color
	\param{in} backcolour Background color
	\param{in} x X position of character
	\param{in} y Y position of character
*/
void putpos(unsigned char c, unsigned char forecolour, unsigned char backcolour, int x, int y);

/**
	\brief Sets the screen to a green color, and blank.
*/
void green_screen();

/**
	\brief Scrolls 1 line.
*/
void scroll_line();

#endif
