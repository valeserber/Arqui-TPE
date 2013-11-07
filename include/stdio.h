#ifndef _STDIO_H
#define _STDIO_H

#define REGOUT 0
#define STDOUT 1
#define STDIN  2
#define STDERR 3
#define EOF    -1

#define putchar(x) putc((x), STDOUT)
#define getchar() getc(STDIN)

int printf(char *fmt, ...);

#endif
