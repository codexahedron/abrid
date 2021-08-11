
#include <ports.h>
#include <screen.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <irq.h>
#include <timer.h>
#include <keyboard.h>
#include <kshell.h>
#include <fs.h>
#include "lib/string.h"
#include "lib/multiboot.h"
#include <panic.h>
#include <types.h>
#include <multibootinfo.h>
#include <usermode.h>

#define MB_MAGIC 0x1BADB002

int main(multiboot_info_t* mb_info, uint32_t magic){
  mbi = mb_info;
  set_cursor_pos(0,0);
  clear(COLOR_WHT, COLOR_BLK);
  kprintf("Loading kernel into memory...");
  putstr("[OK]\n", COLOR_GRN, COLOR_BLK);
  kprintf("Checking GRUB's memory map...");
  if(!(mb_info->flags >> 6 & 0x1)) {
	  	putstr("[FAIL]\n", COLOR_RED, COLOR_BLK);
        panic("invalid memory map given by GRUB bootloader", MEMORY_MAP_INVALID);
  } 
  putstr("[OK]\n", COLOR_GRN, COLOR_BLK);
  //install and initialize everything
  gdt_install();
  idt_install();
  isr_install();
  irq_install();
  timer_install();
  filesystem_init();
  kshell_init();
  keyboard_install();
  malloc_init();
  __asm__ __volatile__("sti");
  // print the welcome message
  kprintf("---------------------------------------------------");
  putstr("\nWelcome to Abrid, an x86 operating system written \nin C from scratch.", COLOR_DGY, COLOR_WHT);
  kprintf("\n---------------------------------------------------\n");
  kprintf(">");
  return 0;
}
