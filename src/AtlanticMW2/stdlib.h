#ifndef __STDLIB_H__
#define __STDLIB_H__

#include <sys/integertypes.h>

// Function prototypes for memory allocation functions
void* malloc(uint32_t size);
void free(void* ptr);
void* realloc(void* ptr, uint32_t size);

#endif  // __STDLIB_H__