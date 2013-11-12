#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"
#include "../../include/string.h"
#include "../../include/video.h"


/***************************************************************
*get_memory
*
* Calcula la cantidad de memoria comenzando en 2MB.
****************************************************************/

size_t get_memory()
{
    size_t bytes=TWO_MB;
    int * mem= (int *)INITIAL_MEM;
    while(mem< (int *)MAX_MEMORY){
        *mem=0;
        if(*mem==0){
            *mem=INT_MIN;
            if(*mem==INT_MIN){
                bytes+=4;
            }
        }
        mem++;
    }
    return bytes;
}

/***************************************************************
*to_string
*
* Convierte de long a char *.
****************************************************************/

char * to_string(char* str, long number)
{
    int i=0;
    if(number==0){
        return "0";
    }
    while(number!=0){
        char n= (number%10)+'0';
        str[i++]=n;
        number /= 10;
    }
    str[i]=0;
    int stop=i--;
    int k=0;
    while(i >= stop/2){
        char aux= str[k];
        str[k++]=str[i];
        str[i--]=aux;
    }
    return str;
}


/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*   Selector a cargar en el descriptor de interrupcion
*   Puntero a rutina de atencion de interrupcion
*   Derechos de acceso del segmento
*   Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset,
        byte access, byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}
