#include "../../include/defs.h"
//#include <stdarg.h>
#include "../../include/stdarg.h"
#include "../../include/stdio.h"
#include "../../include/string.h"
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
    va_list ap;
    char *p, *sval;
    int ival;
    char auxBuf[32];
    int printedChars = 0;

    va_start(ap, fmt);
    for(p = fmt; *p; p++){
        if(*p != '%'){
            putchar(*p);
	    printedChars++;
        }else{
	    switch(*++p){
	    case 'i':
            case 'd':
	        printedChars += printf(ltoa(va_arg(ap, int), auxBuf,10));
	        break;
	    case 'x':
	        printedChars += printf(ltoa(va_arg(ap, int),auxBuf, 16));
		break;
            case 's':
	        for(sval = va_arg(ap, char*); *sval; sval++){
		    putchar(*sval);
		    printedChars++;
		}
		break;
            case 'f':
	    	break;
            } 
	}
    }           
    va_end(ap);
    _Sti();
    return printedChars;
}
