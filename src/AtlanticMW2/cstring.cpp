#include "Includes.h"

// Convert a string to an integer
int atoi(const char* str) {
	int result = 0;
	for (int i = 0; str[i] != '\0'; ++i)
		result = result * 10 + str[i] - '0';
	return result;
}

// Compare memory regions
int memcmp(const void* s1, const void* s2, size_t n) {
	const unsigned char* p1 = (const unsigned char*)s1, * p2 = (const unsigned char*)s2;
	while (n--)
		if (*p1 != *p2)
			return *p1 - *p2;
		else
			*p1++, * p2++;
	return 0;
}

// Copy memory from source to destination
void* memcpy(void* dest, const void* src, size_t count) {
	char* destination = (char*)dest;
	const char* source = (const char*)src;
	--source;
	--destination;

	while (count--) {
		*++destination = *++source;
	}
	return dest;
}

// Fill memory with a constant byte
void* memset(void* m, int c, size_t n) {
	char* s = (char*)m;
	while (n-- != 0) {
		*s++ = (char)c;
	}
	return m;
}

// Calculate the length of a string
size_t strlen(const char* s) {
	const char* p = s;
	while (*s) ++s;
	return s - p;
}

// Tokenize a string
char* str_tok(char* src, char* delimiters) {
	static char* sr;

	if (src)
		sr = src;

	char* temp = sr, * token;
	int i = 0;

	for (; *temp; temp++) {
		for (i = 0; delimiters[i]; i++) {
			if (delimiters[i] == *temp)
				break;
		}
		if (delimiters[i]) {
			*temp = 0;
			if (temp == sr)
				sr++;
			else {
				++temp;
				break;
			}
		}
	}

	if (!(*sr))
		return 0;
	token = sr;
	sr = temp;
	return token;
}

// Copy the first n characters of a string
char* strncpy(char* destination, const char* source, size_t n) {
	char* saver = destination;
	while (n--)
		*saver++ = *source++;
	*saver = '\0';
	return destination;
}

// Compare the first n characters of two strings
int strncmp(const char* s1, const char* s2, size_t n) {
	for (; n--; ++s1, ++s2) {
		if (*s1 != *s2) {
			return *s1 - *s2;
		}
	}
	return 0;
}

// Compare two strings
int strcmp(const char* s1, const char* s2) {
	while (*s1 && (*s1 == *s2))
		s1++, s2++;
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

// Concatenate two strings
char* strcat(char* destination, const char* source) {
	char* ret = destination;
	while (*destination)
		destination++;
	while (*destination++ = *source++);
	return ret;
}

// Tokenize a string using strtok
char* strtok(char* str, char* delimiters) {
	static int pos;
	static char* s;
	int i = 0, start = pos;

	if (str != NULL)
		s = str;

	i = 0;
	int j = 0;
	while (s[pos] != '\0') {
		j = 0;
		while (delimiters[j] != '\0') {
			if (s[pos] == delimiters[j]) {
				s[pos] = '\0';
				pos = pos + 1;
				if (s[start] != '\0')
					return (&s[start]);
				else {
					start = pos;
					pos--;
					break;
				}
			}
			j++;
		}
		pos++;
	}
	s[pos] = '\0';
	if (s[start] == '\0')
		return NULL;
	else
		return &s[start];
}

// Find the first occurrence of a substring in a string
char* strstr(char* s1, const char* s2) {
	if (!s1 || !s2)
		return 0;

	for (; *s1; s1++) {
		const char* h, * n;
		for (h = s1, n = s2; *h && *n && (*h == *n); ++h, ++n) {

		}
		if (*n == '\0') {
			return s1;
		}
	}
	return 0;
}

// Concatenate a character to a string
char chcat(char* destination, char source) {
	if (*destination != '\0')
		while (*(++destination));
	return (*(destination++) = source);
}

// Copy a string from source to destination
char* strcpy(char* dest, const char* src) {
	char* original = dest;
	while ((*dest++ = *src++) != '\0')
		;
	return original;
}

// Convert a string to lowercase
#include <ctype.h>
char* stolower(char* s) {
	for (; *s; s++)
		*s = tolower(*s);
	return s;
}
