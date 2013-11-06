#include "../../include/defs.h"
//#include <stdarg.h>
#include "../../include/stdarg.h"
#include "../../include/stdio.h"
#include "../../include/string.h"

int vfprintf(int fd, const char * fmt, va_list ap);

int putc(int c, int fd){
    unsigned char ch = c;
    write(fd, &ch, 1);
    return c;
}

int getc(int fd){
    int c;
    read(fd, &c, 1);
    return c;
}

int vfprintf(int fd, const char * fmt, va_list ap){
    char *p, *sval;
    int ival;
    char auxBuf[sizeof(int)*8+1]; // Big enough to contain any possible value
    int printedChars = 0;

    for(p = fmt; *p; p++){
        if(*p != '%'){
            putc(*p, fd);
	    printedChars++;
        }else{
	    switch(*++p){
	    case 'i':
            case 'd':
	        printedChars += vfprintf(fd, ltoa(va_arg(ap, int), auxBuf,10), ap);
	        break;
	    case 'x':
	        printedChars += vfprintf(fd, ltoa(va_arg(ap, int),auxBuf, 16), ap);
		break;
            case 's':
	        for(sval = va_arg(ap, char*); *sval; sval++){
		    putc(*sval, fd);
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

int printf(char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    int ret = vfprintf(STDOUT, fmt, ap);
    va_end(ap);
    return ret;
}

int uprintf(char *fmt, ...){
    va_list ap;
    va_start(ap, fmt);
    int ret = vfprintf(REGOUT, fmt, ap);
    va_end(ap);
    return ret;
}
