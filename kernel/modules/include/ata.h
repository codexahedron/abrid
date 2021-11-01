/**
  \file      ata.h
  \brief     ATA driver.
  \details   This header file is used as an ATA driver.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/
 

#ifndef __ATA_H

#define __ATA_H

#include <types.h>

/**
  \def STATUS_BSY
  \brief Busy status for ATA

  Defines the busy status for the ATA driver with hex 0x80.
*/
#define STATUS_BSY 0x80
/**
  \def STATUS_RDY
  \brief Ready status for ATA
  
  Defines the ready status for the ATA driver with hex 0x40.
*/
#define STATUS_RDY 0x40
/**
  \def STATUS_DRQ
  \brief Data transfer requested status for ATA
  
  Defines the "data transfer requested" status for the ATA driver with hex 0x08.
*/
#define STATUS_DRQ 0x08
/**
  \def STATUS_DF
  \brief Device fault status for ATA
  
  Defines the device fault status for the ATA driver with hex 0x20.
*/
#define STATUS_DF 0x20
/**
  \def STATUS_ERR
  \brief Device error status for ATA
  
  Defines the error status for the ATA driver with hex 0x01.
*/
#define STATUS_ERR 0x01

/** 
   \brief Reads a sector from the hard drive

   Reads sector_count*512 bytes from the hard drive in ATA PIO mode.
   \param{out} target_address The target to modify when the function is finished. When the function is done running, `target` will have all 512 bytes in it.
   \param{in} LBA The amount of sectors to offset the read by (0x0 = first sector, 0x1 = second sector, etc.)
   \param{in} sector_count The amount of sectors in total to read. The sectors read are equal to {LBA<x<LBA+sector_count}
*/
void sect_read_atapio(uint32_t target_address, uint32_t LBA, uint8_t sector_count);
/** 
   \brief Writes a sector to the hard drive

   Writes sector_count*512 bytes from the hard drive in ATA PIO mode.
   \param{in} LBA The amount of sectors to offset the read by (0x0 = first sector, 0x1 = second sector, etc.)
   \param{in} sector_count The amount of sectors in total to read. The sectors read are equal to {LBA<x<LBA+sector_count}
   \param{in} bytes The bytes to write to the sector(s).
*/
void sect_write_atapio(uint32_t LBA, uint8_t sector_count, uint32_t* bytes);

/**
	\brief Waits until the hard drive is not busy

	Contains a while() loop that waits until the hard drive is no longer busy.
*/
static void wait_ata_bsy();
/**
	\brief Waits until the hard drive is requesting data

	Contains a while() loop that waits until the hard drive is requesting data.
*/
static void wait_ata_drq();

#endif