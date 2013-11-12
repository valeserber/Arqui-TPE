#include "../../include/defs.h"
#include "../../include/string.h"

/***************************************************************
*strlen
*
* Devuelve la longitud del string.
****************************************************************/

size_t strcmp(const char *s, const char *t){
    while(*s && (*s == *t)) s++, t++;
    return *(const unsigned char*)s - *(const unsigned char*)t;
}

size_t strlen(const char * str){
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
    if(radix < 2 || radix > 16) return NULL;
    if(value==0) return "0";
    
    int i=0;
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

int atohexa(char * buffer){
   int ans=0;
   int base=16;
   int n;
   if((*buffer)=='\0') return 0;
   int i=0;
   int l=strlen(buffer);
   
   char * aux;
   for(i=0;i<l;i++){
	aux[i]=0;
   }
   i=0;
     
   int stop=l-1;
   while(buffer[i]){
        if(isxdigit(buffer[i])){
		aux[stop--]=buffer[i++];
	}
	else{
		return 0;
	}
   }
  
   i=0;
   n=hexatoint(aux[i++]);
   ans=ans+n;
   while(i<l){
        n=hexatoint(aux[i++]);
        ans=ans+(n*base);
        base*=base;
   }
   return ans;
}

int hexatoint(char n){
   int num=0;
   switch(n){
	case 'A':
 	case 'a': return 10;
			break;
	case 'B':
	case 'b': return 11;
			break;
	case 'c':
	case 'C': return 12;
			break;
	case 'd':
	case 'D': return 13;
			break;
	case 'e':
	case 'E': return 14;
			break;
	case 'f':
	case 'F': return 15;
			break;
	default:
		  num=n-'0';
		  break;
   }
  return num;
}

int atoi(const char * str){
    int signflag = 0;
    int value = 0;
    int c;
    while( (c = *str++) ){
        if(*str == '-'){
	    signflag++;
	}else if(!isspace(*str)){
	    break; 
	}
    }
    while((c -= '0') >= 0 && c <= 9){
        value *= 10;
        value += c;
        c = *str++;
    }
    return (signflag % 2 == 0)? value : -value;
}
