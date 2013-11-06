#ifndef _STDIO_H
#define _STDIO_H

#define REGOUT 0
#define STDOUT 1
#define STDIN  2
#define STDERR 3

#define putchar(x) putc((x), STDOUT)

int printf(char *fmt, ...);

#endif
