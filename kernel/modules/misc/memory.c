#include <memory.h>
#include <multibootinfo.h>
uintptr_t current_break;
int has_initialized = 0;
void *managed_memory_start;
void *last_valid_address;
typedef struct mem_control_block {
  int is_available;
  int size;
} mem_control_block;
mem_control_block pmcb; 
#define asizeof(x) ((char *)(&x + 1) - (char *)&x)

	
int ram_size() {
	return (mbi->mem_lower + mbi->mem_upper)+513;
}

unsigned char *memcpy(unsigned char *dest, const unsigned char *src, int count)
{
  int i;
  for (i=0; i<count;i++) dest[i]=src[i];
  return dest;
}

unsigned char *memset(unsigned char *dest, unsigned char val, int count)
{
  int i;
  for (i=0; i<count;i++) dest[i]=val;
  return dest;
}

unsigned short *memsetw(unsigned short *dest, unsigned short val, int count)
{
  int i;
  for (i=0; i<count;i++) dest[i]=val;
  return dest;
}


int memcmp(const void *s1, const void *s2, int len) {
    unsigned char *p = s1;
    unsigned char *q = s2;
    int charCompareStatus = 0;
    if (s1 == s2)
    {
        return charCompareStatus;
    }
    while (len > 0)
    {
        if (*p != *q) {
            charCompareStatus = (*p >*q)?1:-1;
            break;
        }
        len--;
        p++;
        q++;
    }
    return charCompareStatus;
}

void *sbrk(intptr_t incr)
{
    uintptr_t old_break = current_break;
    current_break += incr;
    return (void*) old_break;
}

void malloc_init() {
  last_valid_address = sbrk(0);
  managed_memory_start = last_valid_address;
  has_initialized = 1;
}
void free(void *firstbyte) {
  mem_control_block *mcb;
  mcb = firstbyte - asizeof(pmcb);
  mcb->is_available = 1;
  return;
}
void *malloc(long numbytes) {
  void *current_location;
  mem_control_block *current_location_mcb;
  void *memory_location;
  if (!has_initialized) {
    malloc_init();
  }
  numbytes = numbytes + asizeof(pmcb);
  memory_location = 0;
  current_location = managed_memory_start;
  while (current_location != last_valid_address) {
    current_location_mcb = (mem_control_block *)current_location;
    if (current_location_mcb->is_available) {
      if (current_location_mcb->size >= numbytes) {
        current_location_mcb->is_available = 0;
        memory_location = current_location;
        break;
      }
    }
    current_location = current_location + current_location_mcb->size;
  }
  if (!memory_location) {
    sbrk(numbytes);
    memory_location = last_valid_address;
    last_valid_address = last_valid_address + numbytes;
    current_location_mcb = memory_location;
    current_location_mcb->is_available = 0;
    current_location_mcb->size = numbytes;
  }
  memory_location = memory_location + asizeof(pmcb);
  return memory_location;
}

void bzero(void *s, int n)
{
  char * c = s; // Can't work with void *s directly.
  int i;
  for (i = 0; i < n; ++i)
    c[i] = '\0';
}