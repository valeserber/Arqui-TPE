#include "../../include/kc.h"
#include "../../include/defs.h"

extern  void _write(char ch, FILE * stream);

/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen()
{
    char *vidmem = (char *) VIDMEM_ADDRESS;
    unsigned int i=0;
    while(i < SCREEN_SIZE){
        vidmem[i++]='-';
        vidmem[i++]=WHITE_TXT;
    };
}

/***************************************************************
*print_hello
*
* Imprime hola mundo en pantalla en modo texto color.
****************************************************************/

void print_hello()
{
    char *vidmem = (char *) VIDMEM_ADDRESS;
    unsigned int i=0;
    unsigned int j=80*15*2;
    char *string = "Hola mundo";
    while(j < (80*15*2)+20){
        vidmem[j++]=string[i++];
        vidmem[j++]=WHITE_TXT;
    };
}

/***************************************************************
*print
*
* Imprime en pantalla en modo texto color.
****************************************************************/

void print(char * string)
{
    char *vidmem = (char *) VIDMEM_ADDRESS;
    unsigned int i=0;
    unsigned int j=0;
    size_t length= strlen(string);
    while(i < length && j < SCREEN_SIZE)
    {
        vidmem[j++]=string[i++];
        vidmem[j++]=WHITE_TXT;
    }
}

/***************************************************************
*strlen
*
* Devuelve la longitud del string.
****************************************************************/

size_t strlen(char * string)
{
    size_t len=0;
    while(string[len]!='\0'){
        len++;
    }
    return len;
}

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

char * to_string(char* string, long number)
{
    int i=0;
    if(number==0){
        return "0";
    }
    while(number!=0){
        char n= (number%10)+'0';
        string[i++]=n;
        number /= 10;
    }
    string[i]=0;
    int stop=i--;
    int k=0;
    while(i >= stop/2){
        char aux= string[k];
        string[k++]=string[i];
        string[i--]=aux;
    }
    return string;
}

/***************************************************************
* putc
*
***************************************************************/
// TODO ver el return
int putc(int c, FILE *stream)
{
    char ch = c;
    _write(ch, stream);
    return c;
}

// void int_80h(int interruption, int fd, ...etc )

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
