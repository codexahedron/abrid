/**
  \file      initrd.h
  \brief     Initrd support.
  \details   This header file is used for initial ramdisk support.
  \author    matthyno
  \version   1.0.0
  \date      2021
  \copyright MIT License.
*/

#ifndef INITRD_H
#define INITRD_H

#include "fs.h"
#include <types.h>

fs_node_t *initrd_root;             // Our root directory node.

/**
  \struct initrd_header_t
  \brief Initrd header typedef struct
  
  Initial ramdisk header type.

  This struct consists of:
	I. nfiles: The number of files in the ramdisk.
*/
typedef struct
{
   uint32_t nfiles; // The number of files in the ramdisk.
} initrd_header_t;

/**
  \struct initrd_file_header_t
  \brief Initrd file header typedef struct
  
  Initial ramdisk file header type.

  This struct consists of:
	I. magic: The magic number, for error checking
	II. name: The filename
	III. offset Offset in the initial ramdisk that the file starts
	IV. length: Length of the file
*/
typedef struct
{
   uint8_t magic;     // Magic number, for error checking.
   int8_t name[64];  // Filename.
   uint32_t offset;   // Offset in the initrd that the file starts.
   uint32_t length;   // Length of the file.
} initrd_file_header_t;

/**
   \brief       Standard initrd read function

   Standard initrd read function.
   \param{in}   node The node to read from
   \param{in}   offset The offset for `node`
   \param{in}   size The amount of bytes to read after `offset`.
   \param{in}   buffer The buffer of characters to be read, in uint8_t* form.
   \returns The size of the buffer.
*/
static uint32_t initrd_read(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);
/**
   \brief       Standard initrd readdir function

   Standard initrd read directory function.
   \param{in}   node The node to read from
   \param{in}   index The index of the directory.
   \returns The size of the buffer.
*/
static struct dirent *initrd_readdir(fs_node_t *node, uint32_t index);
/**
   \brief       Standard initrd finddir function

   Standard initrd find directory function.
   \param{in}   node The parent node to search from
   \param{in}   name The name of the directory.
   \returns The size of the buffer.
*/
static fs_node_t *initrd_finddir(fs_node_t *node, char *name);

// Initialises the initial ramdisk. It gets passed the address of the multiboot module,
// and returns a completed filesystem node.
fs_node_t *initialise_initrd(uint32_t location);


#endif