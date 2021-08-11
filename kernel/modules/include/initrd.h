#ifndef INITRD_H
#define INITRD_H

#include "fs.h"
#include <types.h>

fs_node_t *initrd_root;             // Our root directory node.

typedef struct
{
   uint32_t nfiles; // The number of files in the ramdisk.
} initrd_header_t;

typedef struct
{
   uint8_t magic;     // Magic number, for error checking.
   int8_t name[64];  // Filename.
   uint32_t offset;   // Offset in the initrd that the file starts.
   uint32_t length;   // Length of the file.
} initrd_file_header_t;

static uint32_t initrd_read(fs_node_t *node, uint32_t offset, uint32_t size, uint8_t *buffer);
static struct dirent *initrd_readdir(fs_node_t *node, uint32_t index);
static fs_node_t *initrd_finddir(fs_node_t *node, char *name);

// Initialises the initial ramdisk. It gets passed the address of the multiboot module,
// and returns a completed filesystem node.
fs_node_t *initialise_initrd(uint32_t location);


#endif