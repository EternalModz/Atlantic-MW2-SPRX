#include "Includes.h"

// Define the starting address for system free memory
#define SYS_FREE_MEMORY 0x1840000

// Custom implementation of malloc function
void* malloc(uint32_t a_uiSize) {
    // Allocate memory from the specified system free memory address
    sys_addr_t l_uiAddr = (sys_addr_t)(SYS_FREE_MEMORY);

    // Align the size to the next multiple of 64KB
    a_uiSize = ((a_uiSize + 65536) / 65536) * 65536;

    // Allocate memory using the system memory allocation function
    sys_memory_allocate(a_uiSize, SYS_MEMORY_PAGE_SIZE_64K, &l_uiAddr);

    // Return the allocated memory address
    return (void*)l_uiAddr;
}

// Custom implementation of free function
void free(void* ptr) {
    // Check if the pointer is not null before freeing the memory
    if (ptr)
        sys_memory_free((sys_addr_t)ptr);
}

// Custom implementation of realloc function
void* realloc(void* ptr, uint32_t size) {
    // Allocate a new block of memory with the specified size
    void* dest = malloc(size);

    // Copy the contents from the old block to the new block
    memcpy(dest, ptr, size);

    // Free the memory associated with the old block
    free(ptr);

    // Return the new block of memory
    return dest;
}