#include <kshell.h>
#include <timer.h>
#include <ports.h>
#include "lib/string.h"
#include "lib/mem.h"
#include <stdio.h>
#include <fs.h>
#include <panic.h>
#define NULL ((char *)0)
#define sizeof(type) (char *)(&type+1)-(char*)(&type)

extern int enable_shell;
fs_node_t blank;
int cf = 1;
int dfs = 1;
void kshell_init(){
	kprintf("Enabling kernel shell...");
	enable_shell = 1;
	putstr("[OK]\n", COLOR_GRN, COLOR_BLK);
}

void kshell(char s[], int i){
	char* start = "";
	char* two = "";
	strcpy(start, s);
	strcpy(two, s);
  	char* cmdnamee = strtok(start, " ");
  if(strcmp(s, "clear")==0){
  	clear_scr();
  } else if(strcmp(s, "help")==0){ // print help information
  	available_commands();
  } else if(strcmp(s, "about")==0){ // print info about computer
  	kprintf("Abrid-x86: a 32 bit operating system written in C and Assembly\n");
  } else if(strcmp(s, "hlt")==0){ // halt the computer
  	halt();
  } else if(strcmp(cmdnamee, "panic")==0) { // kernel panic
	  panic("Kernel panic created by `panic` command", USER_CREATED_PANIC);
  } else if(strcmp(s, "reboot")==0){ // reboot computer
  	reboot();
  } else if(strcmp(s, "unknownerror")==0){ // prints unknown error
    	kprintf("Printing unknown error:\n");
  	unknown_command(s);
  } else if(strcmp(s, "sec")==0) { // get seconds elapsed from startup
  	char *buf;
  	char *str = itoa(get_tracked_seconds(), buf, 10);
  	strcat(str, "\n");
  	kprintf(str);
  } else if(strcmp(cmdnamee, "echo")==0) { // echo message after "echo "
	kprintf(strremove(s,"echo "));
  }else if(strcmp(s, "ls")==0) { // list files and kprintf it
	struct dirent *node = 0;
	int i=0;
	while ( (node = readdir_fs(fs_root, i)) != 0)
	{
		fs_node_t *fsnode = finddir_fs(fs_root, node->name);
		kprintf(node->name);
		if(((fsnode->flags&0x7) == FS_DIRECTORY)) 
		{
			kprintf("/");
		}
		kprintf("\n");
		i++;
	} 
  } else if(strcmp(cmdnamee, "cat")==0) { // read file and kprintf it
	  char buf[4096];
		fs_node_t *fsnode = finddir_fs(fs_root, strremove(s,"cat "));
		uint32_t sz = read_fs(fsnode, 0, 4096, buf);
		int j;
		for (j = 0; j < sz; j++)
			kprintc(buf[j]);
	  kprintf("\n");
  } else if(strcmp(cmdnamee, "\\\/")==0 || s == "") { // comment
	
  } else if(strcmp(s, "ram")==0) { // list amount of RAM installed
	char* buf;
	kprintf(itoa(ram_size(), buf, 10));
  } else { // unknown command
  	unknown_command(s);
  }

  for(int j=0; s[j]!='\0'; j++){
  	s[j]='\0';
  }
  // strcat(strcat(strcat(strcat("[", username), "("), errorcode), ")]$")
  kprintf(">");
}

void halt(){
  	kprintf("Halting system...");
  	putstr("[DONE]", COLOR_GRN, COLOR_BLK);
  	asm volatile("hlt");
}

void reboot(){
  	kprintf("Rebooting...\n");
  	//using 8042 keyboard controller to pulse the CPU's RESET Pin
  	unsigned char temp = 0x02;
  	while(temp & 0x02)
  		temp = in_port_byte(0x64);
  	out_port_byte(0x64, 0xFE);
  	asm volatile("hlt");	
}

void clear_scr(){
	clear(COLOR_WHT, COLOR_BLK);
	set_cursor_pos(0,0);
}

void available_commands(){
    kprintf("Available commands:\n");
	kprintf("`help` Shows this screen.\n`clear` Clears the screen\n`about` Shows information about the OS.\n`hlt` Halts the computer.\n`reboot`Reboots the computer.\n`echo <[Any] msg>` Prints any characters after \"echo \".\n`cat <[Any] file>` Prints the contents of the file `file`.\n`ls` Prints a list of all the files and directories in the current directory.\n");
}

void unknown_command(char s[]){
	kprintf(s);
  	putstr(" : command not found!\n", COLOR_RED, COLOR_BLK);
  	putstr("Type ", COLOR_GRY, COLOR_BLK);
  	putstr("\"help\" ", COLOR_YEL, COLOR_BLK);
  	putstr("for the list of available commands.\n", COLOR_GRY, COLOR_BLK);
}
