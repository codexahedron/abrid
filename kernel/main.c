#include <ports.h>
#include <screen.h>
#include <gdt.h>
#include <idt.h>
#include <isr.h>
#include <irq.h>
#include <timer.h>
#include <keyboard.h>
#include <fs.h>
#include <string.h>
#include <multiboot.h>
#include <panic.h>
#include <types.h>
#include <multibootinfo.h>
#include <man.h>
#include <ata.h>

#define MB_MAGIC 0x1BADB002

int main(multiboot_info_t* mb_info, uint32_t magic){
  mbi = mb_info;
  set_cursor_pos(0,0);
  clear(COLOR_WHT, COLOR_BLK);
  kprintf("---loading kernel\n\\->");
  putstr("done.\n", COLOR_GRN, COLOR_BLK);
  kprintf("---checking grub's memory map\n\\->");
  if(!(mb_info->flags >> 6 & 0x1)) {
	  	putstr("fail.\n", COLOR_RED, COLOR_BLK);
        panic("invalid memory map given by GRUB bootloader", MEMORY_MAP_INVALID);
  } 
  putstr("done.\n", COLOR_GRN, COLOR_BLK);
  //install and initialize everything
  gdt_install();
  idt_install();
  isr_install();
  irq_install();
  timer_install();
  filesystem_init();
  shell_init();
  keyboard_install();
  malloc_init();
  manpage_init();
  ata_init();
  __asm__ __volatile__("sti");

  // print the welcome message
  putstr("Welcome to ", COLOR_GRY, COLOR_BLK);
  putstr("Abrid\n", COLOR_CYN, COLOR_BLK);
  kprintf(">");
  return 0;
}
