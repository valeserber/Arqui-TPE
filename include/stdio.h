#ifndef _STDIO_H
#define _STDIO_H

#define REGOUT 0
#define STDOUT 1
#define STDIN  2
#define STDERR 3
#define EOF    -1

#define putchar(x) putc((x), STDOUT)
#define getchar() getc(STDIN)

/*
 * Write a single character to the specified file descriptor
 */
int putc(int c, int fd);

/*
 * Gets the next character from the specified file descriptor while
 * modifying its position indicator
 */
int getc(int fd);

/*
 * Writes the string pointed by fmt to the file descriptor, replacing any
 * format specifier using the elements in the variable argument list
 */
int vfprintf(int fd, const char * fmt, va_list ap);

/*
 * Writes the C string pointed by fmt to the standard output. If fmt includes
 * format specifiers (subsequences beginning with %), the additional
 * arguments following fmt are formatted and inserted in the resulting
 * string replacing their respective specifiers.
 */
int printf(char *fmt, ...);

/*
 * Works identically to printf except it prints to the register output
 * (i.e. the upper 10x80 screen).
 */
int uprintf(char *fmt, ...);

void printFlags(dword flags);

int scanf(const char * fmt, ...);
#endif
