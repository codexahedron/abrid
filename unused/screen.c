#include <ports.h>
#include <screen.h>
#include <stdarg.h>
#include "lib/string.h"

volatile vga_char *TEXT_AREA = (vga_char*) VGA_START;

unsigned char vga_color(const unsigned char fg_color, const unsigned char bg_color){
    // Put bg color in the higher 4 bits and mask those of fg
    return (bg_color << 4) | (fg_color & 0x0F);
}


void clear(unsigned char fg_color, unsigned char bg_color){
    const char space = ' ';
    unsigned char clear_color = vga_color(fg_color, bg_color); // Creates a vga color based off of the fg and bg color

    const vga_char clear_char = { // Creates a vga_char
        .character = space, // with the character being blank
        .style = clear_color // and the color being the previously defined clear_color
    };

    for(unsigned long i = 0; i < VGA_EXTENT; i++) { // Loops over the extent of the vga screen 
        TEXT_AREA[i] = clear_char; // and sets every character to the previously defined clear_char
    }
}


void putchar(const char character, const unsigned char fg_color, const unsigned char bg_color){
    unsigned short position = get_cursor_pos(); // Get the cursor position

    if (character == '\n'){ // If the character is a newline, then set the cursor x and y to 0 and y+1 respectively. If the screen is on the last row of text, scroll
        unsigned char current_row = (unsigned char) (position / VGA_WIDTH); 

        if (++current_row >= VGA_HEIGHT){
            scroll_line();
        }
        else{
            set_cursor_pos(0, current_row);
        }
    }
    else if(character == '\b'){ // If the character is a backspace, then move the cursor position to (x-1, y), set the character to a blank character, and then move the character back again.
        move_back_cursor();
        putchar(' ', fg_color, bg_color);
        move_back_cursor();
    }
    else if (character == '\r'){ // If the character is a carriage return, then set the cursor position to (0, pos/vga_width), usually (0, pos/80)
        unsigned char current_row = (unsigned char) (position / VGA_WIDTH);

        set_cursor_pos(0, current_row);
    }

    else if (character == '\t'){ // If the character is a tab, then turn the tab into 4 spaces and advance the cursor to the end of the 4 spaces.
        // Turn tab to 4 spaces
        for (unsigned char i = 0; i < 4; i++){
            putchar(' ', fg_color, bg_color);
        }
        advance_cursor();
    }

    else { // If the character is just a regular character, no escape character, then simply print the colored character, and advance the cursor.
        unsigned char style = vga_color(fg_color, bg_color);
        vga_char printed = {
            .character = character,
            .style = style
        };

        TEXT_AREA[position] = printed;

        advance_cursor();
    }
}


void putstr(const char *string, const unsigned char fg_color, const unsigned char bg_color){
    while (*string != '\0'){ // Get each character of the string until the \0 character and print it
        putchar(*string++, fg_color, bg_color);
    }
}
void kprintc(const char *ch) {
	putchar(ch, COLOR_WHT, COLOR_BLK); // Print 1 character, but white
} 
void kprintf(const char *string){
    while(*string != '\0'){ // Print string, but white
        putchar(*string++, COLOR_WHT, COLOR_BLK);
    }
}
void printf(char *format, ...) {
    va_list ap;
    va_start(ap, format);

    char *ptr = format;

  	while(*ptr) {
		if (*ptr == '%') {
			ptr++;
			char* buf;
			switch (*ptr++) {
				case 's':
					kprintf(va_arg(ap, char *));
					break;
				case 'd':
					kprintf(itoa(va_arg(ap, char *), buf, 10));
					break;
			}
		} else {
			kprintc(*ptr++);
		}
  	}

  	va_end(ap);
}





unsigned short get_cursor_pos(){
    unsigned short position = 0;

    out_port_byte(CURSOR_PORT_COMMAND, 0x0F); // Out port byte 0x0F
    position |= in_port_byte(CURSOR_PORT_DATA);

    out_port_byte(CURSOR_PORT_COMMAND, 0x0E); // Out port byte 0x0E
    position |= in_port_byte(CURSOR_PORT_DATA) << 8; // Combine the two so that they can be factored out easily, but are still 1 number

    return position;
}


void show_cursor(){ // Sends a bunch of out port byte commands to show the cursor
    unsigned char current;

    out_port_byte(CURSOR_PORT_COMMAND, 0x0A);
    current = in_port_byte(CURSOR_PORT_DATA);
    out_port_byte(CURSOR_PORT_DATA, current & 0xC0);

    out_port_byte(CURSOR_PORT_COMMAND, 0x0B);
    current = in_port_byte(CURSOR_PORT_DATA);
    out_port_byte(CURSOR_PORT_DATA, current & 0xE0);
}


void hide_cursor(){ // Sends a couple out port byte commands to hide the cursor
    out_port_byte(CURSOR_PORT_COMMAND, 0x0A);
    out_port_byte(CURSOR_PORT_DATA, 0x20);
}


void advance_cursor(){
    unsigned short pos = get_cursor_pos(); // Gets the cursor position
    pos++; // and increments it by 1

    if (pos >= VGA_EXTENT){ // If the positon >= VGA_EXTENT, scroll
        scroll_line();
    }

	// This just sends a bunch of out port byte commands to set the cursor position forward
    out_port_byte(CURSOR_PORT_COMMAND, 0x0F);
    out_port_byte(CURSOR_PORT_DATA, (unsigned char) (pos & 0xFF));

    out_port_byte(CURSOR_PORT_COMMAND, 0x0E);
    out_port_byte(CURSOR_PORT_DATA, (unsigned char) ((pos >> 8) & 0xFF));
}

void move_back_cursor(){
    unsigned short pos = get_cursor_pos(); // Gets the cursor position
    pos--; // and decrements it by 1

	// This just sends a bunch of out port byte commands to set the cursor position backward
    out_port_byte(CURSOR_PORT_COMMAND, 0x0F);
    out_port_byte(CURSOR_PORT_DATA, (unsigned char) (pos & 0xFF));

    out_port_byte(CURSOR_PORT_COMMAND, 0x0E);
    out_port_byte(CURSOR_PORT_DATA, (unsigned char) ((pos >> 8) & 0xFF));
}

void set_cursor_pos(unsigned char x, unsigned char y){
    unsigned short pos = (unsigned short) x + ((unsigned short) VGA_WIDTH * y); // Factors the cursor position together like get_cursor_pos

    if (pos >= VGA_EXTENT){ // If pos >= VGA_EXTENT, set pos to VGA_EXTENT minus 1
        pos = VGA_EXTENT - 1;
    }

	// This just sends a bunch of out port byte commands to set the cursor position
    out_port_byte(CURSOR_PORT_COMMAND, 0x0F);
    out_port_byte(CURSOR_PORT_DATA, (unsigned char) (pos & 0xFF));

    out_port_byte(CURSOR_PORT_COMMAND, 0x0E);
    out_port_byte(CURSOR_PORT_DATA, (unsigned char) ((pos >> 8) & 0xFF));
}


void scroll_line(){
    // Moves all the lines up one
    for(unsigned short i = 1; i < VGA_HEIGHT; i++){
        for(unsigned short j = 0; j < VGA_WIDTH; j++){
            unsigned short to_pos = j + ((i - 1) * VGA_WIDTH);
            unsigned short from_pos = j + (i * VGA_WIDTH);

            TEXT_AREA[to_pos] = TEXT_AREA[from_pos];
        }
    }

    // and clears the bottommost row
    unsigned short i = VGA_HEIGHT - 1;
    for(unsigned short j = 0; j < VGA_WIDTH; j++){
        unsigned short pos = j + (i * VGA_WIDTH);

        vga_char current = TEXT_AREA[pos];
        vga_char clear = {
            .character=' ',
            .style = current.style
        };

        TEXT_AREA[pos] = clear;
    }
	// then sets the cursor y to the second-to-bottommost row
    set_cursor_pos(0, VGA_HEIGHT - 1);
}