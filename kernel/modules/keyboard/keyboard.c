#include <ports.h>
#include <screen.h>
#include <isr.h>
#include <irq.h>
#include <keyboard.h>
#include <shell.h>
#include <modules.h>

#define sizeof(type) (char *)(&type+1)-(char*)(&type)

//shamelessly copied this from bkerndev
int enable_shell=0;
char *buffer="";
unsigned char ascii_values[128] =
{
    0,  27, '1', '2', '3', '4', '5', '6', '7', '8',	/* 9 */
  '9', '0', '-', '=', '\b',	/* Backspace */
  '\t',			/* Tab */
  'q', 'w', 'e', 'r',	/* 19 */
  't', 'y', 'u', 'i', 'o', 'p', '[', ']', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'a', 's', 'd', 'f', 'g', 'h', 'j', 'k', 'l', ';',	/* 39 */
 '\'', '`',   0,		/* Left shift */
 '\\', 'z', 'x', 'c', 'v', 'b', 'n',			/* 49 */
  'm', ',', '.', '/',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    '$',	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

unsigned char ascii_values_shift[128] =
{
    0,  27, '!', '@', '#', '$', '%', '^', '&', '*',	/* 9 */
  '(', ')', '_', '+', '\b',	/* Backspace */
  '\t',			/* Tab */
  'Q', 'W', 'E', 'R',	/* 19 */
  'T', 'Y', 'U', 'I', 'O', 'P', '{', '}', '\n',	/* Enter key */
    0,			/* 29   - Control */
  'A', 'S', 'D', 'F', 'G', 'H', 'J', 'K', 'L', ':',	/* 39 */
 '\"', '~',   0,		/* Left shift */
 '|', 'Z', 'X', 'C', 'V', 'B', 'N',			/* 49 */
  'M', '<', '>', '?',   0,				/* Right shift */
  '*',
    0,	/* Alt */
  ' ',	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  '-',
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  '+',
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};
//string buffer to keep track of user's entry
char input_buffer[256];
int i = 0; //integer to keep track of length
int shiftmarker = 0;
void keyboard_handler(struct regs *r){
    unsigned char scancode;

    //Read the Keyboard's data port
    scancode = in_port_byte(0x60);

    if(scancode & 0x80){
        //use Shift, Alt, CTRL keys here
    }
    else{
        char c = ascii_values[scancode];
		if(c == '$') {
			if(shiftmarker == 0) {
				shiftmarker = 1;
			} else {
				shiftmarker = 0;
			}
		}
		 if(i==0 && c=='\b'){
          //do nothing
          //this prevents clearing the '>' character on the screen
        }
        else{
		  if(c != '$' && shiftmarker == 0) {
          	putchar(c, COLOR_WHT, COLOR_BLK);
			track_input(c);
		  } else if(c != '$' && shiftmarker == 1) {
			  putchar(ascii_values_shift[scancode], COLOR_WHT, COLOR_BLK);
			  track_input(ascii_values_shift[scancode]);
		  }
        }
    }

}
char get_key(){
    unsigned char scancode;

    //Read the Keyboard's data port
    scancode = in_port_byte(0x60);
	char *buf;
	kprintf(itoa(scancode, buf, 10));
    if(scancode & 0x80){
        //use Shift, Alt, CTRL keys here
    }
    else{
        char c = ascii_values[scancode];
		return c;
    }
	return 0;

}

/*void parse_input(char *input, int i) {
	if(enable_shell==1) {
		strcpy(buffer, input);
		kshell(input, i);
	} else {
		strcpy(buffer, input);
	}
}*/
void track_input(char c){
          //If user hits enter, we can execute the command
        if(c == '\n'){
          //handle shell support here
          //parse_input(input_buffer, i);
		  shell(input_buffer, i);
		  memset(input_buffer, 0, sizeof(input_buffer));
          i=0;
        }
        //handle backspace in input string buffer
        else if(c == '\b'){
          input_buffer[i-1]='\0';
          i--;
        }
        //handle the input buffer if the input is greater than 31
        else if(i >= 255){
          input_buffer[0]='\0';
          i = 0;
		}
		else {
          input_buffer[i]=c;
          i++;
        }
        //add new input characters from input to string buffer
}

void keyboard_install(){
	module_t modules_keyboard_keyboard = MODULE("kernel.modules.keyboard.keyboard", "Provides PS/2 keyboard support for the kernel (CORE)\n\nThis allows users to use an essential feature of any interactive operating system - \n the keyboard.");
    irq_install_handler(1, keyboard_handler);
    INIT(modules_keyboard_keyboard);
}