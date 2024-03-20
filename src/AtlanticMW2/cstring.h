#ifndef __CSTRING_H__
#define __CSTRING_H__

// Convert string to integer
int atoi(const char* str);

// Compare memory blocks
int memcmp(const void* s1, const void* s2, size_t n);

// Copy memory from source to destination
void* memcpy(void* dest, const void* src, size_t count);

// Set a block of memory to a specific value
void* memset(void* ptr, int value, size_t num);

// Get the length of a string
size_t strlen(const char* str);

// Tokenize string using a delimiter
char* str_tok(char* src, char* deli);

// Copy a portion of a string to another string
char* strncpy(char* s, const char* ct, size_t n);

// Tokenize string using a delimiter (alternative function)
char* strtok(char* str, char* comp);

// Compare two strings
int strcmp(const char* str1, const char* str2);

// Compare the first n characters of two strings
int strncmp(const char* s1, const char* s2, size_t n);

// Concatenate two strings
char* strcat(char* destination, const char* source);

// Find the first occurrence of a substring in a string
char* strstr(char* s1, const char* s2);

// Concatenate a character to a string
char chcat(char* destination, char source);

// Copy a string to another string
char* strcpy(char* dest, const char* src);

// Convert string to lowercase
char* stolower(char* s);

#endif