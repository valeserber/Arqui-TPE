#include "../../include/stdio.h"
#define putchar(x) putc((x), STDOUT)

/* TODO averiguar como usar typedefs a FILE* para stdin, stdout, stderr
 * y la buscar las macros va_end, va_start, va_args
 */
int printf(const char * fmt, ...){
    va_list ap;
    char *p;
    int i = 0
    va_start(ap, fmt);
    for(p = fmt; *p; p++){
        if(*p != '%'){
            putchar(*p);
        }
     //   else switch(*++p){
     //       case ´d´:
    }           
    va_end(ap);
}
