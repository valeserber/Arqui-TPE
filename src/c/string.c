#include "../../include/defs.h"
#include "../../include/string.h"


/***************************************************************
*strlen
*
* Devuelve la longitud del string.
****************************************************************/

size_t strlen(const char * str)
{
    size_t len = 0;
    while(str[len] != 0){
    	len++;
    }
    return len;
}

char* ltoa(long value, char *buffer, int radix){
    char symbol[] = {
    '0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
    'A', 'B', 'C', 'D', 'E', 'F'};  
    if(radix < 2 || radix > 16){
        return NULL;
    }
    int i=0;
    if(value==0){
        return "0";
    }
    while(value){
        buffer[i++] = symbol[value%radix];
        value /= radix;
    }
    buffer[i]=0;
    int stop=i--;
    int k=0;
    while(i >= stop/2){
        char aux= buffer[k];
        buffer[k++]=buffer[i];
        buffer[i--]=aux;
    }
    return buffer;
}
