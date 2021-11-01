#include <ata.h>

#include <modules.h>
#include <ports.h>
#include <types.h>
#include <screen.h> //temp

void sect_read_atapio(uint32_t target_address, uint32_t LBA, uint8_t sector_count) {

	wait_ata_bsy();
	
  out_port_byte(0x1F6,0xE0 | ((LBA >>24) & 0xF));
	
	out_port_byte(0x1F2, sector_count);
	
	out_port_byte(0x1F3, (uint8_t) LBA);
	
	out_port_byte(0x1F4, (uint8_t)(LBA >> 8));
	
	out_port_byte(0x1F5, (uint8_t)(LBA >> 16)); 
	
	out_port_byte(0x1F7,0x20); // Send the read command!
	

	uint16_t *target = (uint16_t*) target_address;
	
	for (int j =0;j<sector_count;j++)
	{
		wait_ata_bsy();
		wait_ata_drq();
		for(int i=0;i<256;i++)
			target[i] = inw(0x1F0);
		target+=256;
	}
	
}
void sect_write_atapio(uint32_t LBA, uint8_t sector_count, uint32_t* bytes) {
	wait_ata_bsy();
	out_port_byte(0x1F6,0xE0 | ((LBA >>24) & 0xF));
	out_port_byte(0x1F2,sector_count);
	out_port_byte(0x1F3, (uint8_t) LBA);
	out_port_byte(0x1F4, (uint8_t)(LBA >> 8));
	out_port_byte(0x1F5, (uint8_t)(LBA >> 16)); 
	out_port_byte(0x1F7,0x30); // Send the write command!

	for (int j =0;j<sector_count;j++)
	{
		wait_ata_bsy();
		wait_ata_drq();
		for(int i=0;i<256;i++)
		{
			outl(0x1F0, bytes[i]);
		}
	}
}

static void wait_ata_bsy() {
	while(inb(0x1F7)&STATUS_BSY);
}
static void wait_ata_drq() {
	while(!(inb(0x1F7)&STATUS_RDY));
}

void ata_init() {
	module_t modules_ata_ata = MODULE("kernel.modules.ata.ata", "Provides ATA support for the kernel, read/write (CORE)");
	INIT(modules_ata_ata);
}