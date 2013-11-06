#include "../../include/defs.h"
#include "../../include/stdarg.h"
#include "../../include/stdio.h"
#include "../../include/string.h"
#define putchar(x) putc((x), STDOUT)
int vfprintf(int fd, const char * fmt, va_list ap);
void printFlags(word flags);

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

void printFlags(word flags){
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
    uprintf("]");
}
/*
void miniscanf(char *fmt, ...){
                        localfmt[i] = '\0';
                        switch(*++p) {
                        case 'd':
                        case 'i':
                                        ival = va_arg(ap, int *);
                                        scanf(localfmt, ival);
                                        break;
                        case 'x':
                        case 'X':
                        case 'u':
                        case 'o':
                                        uval = va_arg(ap, unsigned *);
                                        scanf(localfmt, uval);
                                        break;
                        case 'f':
                                        dval = va_arg(ap, double *);
                                        scanf(localfmt, dval);
                                        break;
                        case 's':
                                        sval = va_arg(ap, char *);
                                        scvanf(localfmt, sval);
                                        break;
                        default:
                                        scanf(localfmt);
                                        break;
                        }
                        i = 0;
        }
        va_end(ap);
}

int scanf(const char * fmt, ...){
    va_list ap;
    char *p, *sval;
}


int scanf(const char * fmt, ...){
	va_list ap; //apunta a cada arg sin nombre en orden
	char *p, *sval, *cval;
	int *ival;
	FILE  fp;
	int read=0,i=0, c,k, j = 0;
	va_start(ap, fmt); //hace que ap apunte al 1er arg sin nombre
	char s[BUFFER_SIZE];
	while((c = getc(&fp)) != '\n' && i < BUFFER_SIZE)
	{
		if(c == '\b' && i >= 1)
			i--;
		if(c != '\b')
		{
			s[i] = c;
			i++;
		}
	}
	s[i] = '\0';
	i = 0;
		for (p = fmt; *p; p++) 
		{
			char aux [BUFFER_SIZE] = {0};

			if(*p != '%')
			{
				c = s[j++];
				if(c =='\0' || *p != c)
					return read;
				continue;
			}
			switch (*++p)
			{
				case 'd':
							i=0;
							ival = va_arg(ap,int *);
							while(s[j] != '\0' && isdigit(s[j]))
							{
								aux[i++] = s[j++];
							}
							aux[i] = '\0';
							if(aux[0] == '\0')
								return read;
							*ival=atoi(aux);
							read++;
							break;
				case 's':
							i = 0;
							sval = va_arg(ap,char *);
							while(s[j] != '\0' && s[j] != ' ')
							{
								aux[i++] = s[j++];
							}
							aux[i] = '\0';
							if(aux[0] == '\0')
								return read;
							
							k = 0;
							while(aux[k] != '\0')
							{
								sval[k] = aux[k];
								k++;
							}
							sval[k] = '\0';
							read++;
							break;
				case 'c':
							cval = va_arg(ap,char*);
							c = s[j++];
							if(c == '\0' )
								return read;
							*cval = c;
							read++;
							break;
				case 'x':
							i=0;
							ival = va_arg(ap,int *);
							while(s[j] != '\0' && (isdigit(s[j]) || ishexa(s[j])))
							{
								aux[i] = s[j];
								i++;
								j++;
							}
							aux[i] = '\0';
							if(aux[0] == '\0')
								return read;
							//*ival=ato(aux, i, 16);
							read++;
							break;
			
				default:
							c = s[j++];
							if(!(c != EOF && c != '\n' && *p == c))
								return read;
							break;
			}
		}
	va_end(ap); // clean up when done
	return read;
}

*/
