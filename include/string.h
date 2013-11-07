#ifndef _STRING_H_
#define _STRING_H_

#define NULL ((void*)0)

size_t strcmp(const char *s, const char *t);
size_t strlen(const char * str);
char* ltoa(long value, char* buffer, int radix);

#endif
