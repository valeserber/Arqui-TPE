#include "../../include/defs.h"
//#include <stdarg.h>
#include "../../include/stdarg.h"
#include "../../include/stdio.h"
#define putchar(x) putc((x), STDOUT)

/***************************************************************
* putc
*
***************************************************************/
// TODO ver el return
/*int putc(int c, FILE *stream)
{
    unsigned char ch = c;
    _write(stream->fd, &ch, 1);
    return c;
}*/

int putc(int c, int fd)
{
    unsigned char ch = c;
    _write(fd, &ch, 1);
    return c;
}

int getc(FILE *stream){
    char c;
    _read(stream->fd, &c, 1);
    return c;
}

/* TODO averiguar como usar typedefs a FILE* para stdin, stdout, stderr
 * y la buscar las macros va_end, va_start, va_args
 */

int printf(char * fmt, ...){
    va_list vap;
    char *p;
    int i = 0;

    va_start(vap, fmt);

    for(p = fmt; *p; p++){
        if(*p != '%'){
            putchar(*p);
        }
     //   else switch(*++p){
     //       case ´d´:
    }           
    va_end(vap);
    return 0;
}

