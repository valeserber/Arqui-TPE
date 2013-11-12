#include "../../include/defs.h"
#include "../../include/stdarg.h"
#include "../../include/stdio.h"
#include "../../include/string.h"
#include "../../include/ctype.h"

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
    char *p, *sval, cval;
    int ival;
    char auxBuf[sizeof(int)*8+1]; //Big enough for any possible ltoa value
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
            case 'X':
	        sval = ltoa(va_arg(ap, int), auxBuf, 16);
                char *aux = sval;
                while (*sval){
                    *sval = toupper(*sval);
                    sval++;
                }
                printedChars+= vfprintf(fd, aux, ap);
                break;
            case 's':
	        for(sval = va_arg(ap, char*); *sval; sval++){
		    putc(*sval, fd);
		    printedChars++;
		}
		break;
            case 'f':
	    	break;
            case 'c':
	        cval = va_arg(ap, char);
		putc(cval, fd);
		printedChars++;
		break;
            }
	}
    }
    va_end(ap);
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

void printFlags(dword flags){
    unsigned int bit = 1;
    uprintf("eflags   0x%x  [", flags);
    flags & bit ? uprintf("C") : uprintf(" ");
    flags & (bit << 2) ? uprintf("P") : uprintf(" ");
    flags & (bit << 4) ? uprintf("A") : uprintf(" ");
    flags & (bit << 6) ? uprintf("Z") : uprintf(" ");
    flags & (bit << 7) ? uprintf("S") : uprintf(" ");
    flags & (bit << 8) ? uprintf("T") : uprintf(" ");
    flags & (bit << 9) ? uprintf("IE") : uprintf("  ");
    flags & (bit << 10) ? uprintf("D") : uprintf(" ");
    flags & (bit << 11) ? uprintf("O") : uprintf(" ");
    uprintf("]\n");
}

int scanf(const char * fmt, ...){
    va_list ap; //apunta a cada arg sin nombre en orden
    char *p, *sval, *cval;
    char s[50];
    int *ival;
    int charsRead=0,i=0, k, j;
    char c;
    va_start(ap, fmt); //hace que ap apunte al 1er arg sin nombre
    while((c = getchar()) != '\n' && i < BUFFER_LENGTH)
    {
        if(c!=0){
            if(c == '\b' && i >= 1){
                i--;
                 putc(c ,1);
            }
            if(c != '\b' && c!='\n'){
                s[i++] = c;
                putc(c ,1);
            }
        }
    }
    s[i] = '\0';

    /* Lo analizo */
    i = 0;
    char aux [50] = {0};
    for (p = fmt, i = 0, j = 0; *p; p++){
        if(*p != '%'){
            c = s[j++];
            if( !c || *p != c) return charsRead;
	    }else switch (*++p){
            case 'd':
                i = 0;
                ival = va_arg(ap,int *);
                while(isdigit(s[j])){
                    aux[i++] = s[j++];
                }
                aux[i] = '\0';
                if(aux[0] == '\0')  return charsRead;
                *ival=atoi(aux);
                charsRead++;
                break;
            case 's':
                i = 0;
                sval = va_arg(ap,char *);
                while(s[j] && s[j] != ' '){
                    aux[i++] = s[j++];
                }
                aux[i] = '\0';
                if(aux[0] == '\0') return charsRead;
                k = 0;
                while(aux[k] != '\0'){
                    sval[k] = aux[k];
                    k++;
                }
                sval[k] = '\0';
                charsRead++;
                break;
            case 'c':
                cval = va_arg(ap,char*);
                c = s[j++];
                if(!c) return charsRead;
                *cval = c;
                charsRead++;
                break;
            case 'x':
                i=0;
                ival = va_arg(ap,int *);
                while(isxdigit(s[j])){
                    aux[i++] = s[j++];
                }
                aux[i] = '\0';
                if(aux[0] == '\0') return charsRead;
                *ival=atohexa(aux);
                charsRead++;
                break;
            default:
                c = s[j++];
                if(c == EOF || c == '\n' || *p != c) return charsRead;
                break;
        }
    }
    va_end(ap);
    return charsRead;
}
