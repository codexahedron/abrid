#ifndef __ABRFS_H
#define __ABRFS_H

#include "types.h"

#define FS_MAX_NAME_LENGTH 63
#define FS_MAGIC "abrfs   "

typedef struct file_t {
	char name[FS_MAX_NAME_LENGTH+1];
	uint32_t size;
	char* bytes;
	int sector_number;
} file_t;
#endif