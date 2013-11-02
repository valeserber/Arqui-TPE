#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"

extern void _write(int fd, const void *buf, size_t count);
extern void _read(int fd, void *buf, size_t count);

//typedef enum {STDIN, STDOUT, STDERR} stream;
//typedef enum {SYS_READ = 3, SYS_WRITE = 4} sys_call;


/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen()
{
    char *vidmem = (char *) VIDMEM_ADDRESS;
    unsigned int i=0;
    while(i < UPPER_SCREEN_SIZE){
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
    unsigned int j=UPPER_SCREEN_SIZE;
    char *string = "Hola mundo";
    while(j < (UPPER_SCREEN_SIZE)+20){
        vidmem[j++]=string[i++];
        vidmem[j++]=WHITE_TXT;
    };
}

/***************************************************************
*print
*
* Imprime en pantalla en modo texto color.
****************************************************************/

void print(char * str)
{
    char *vidmem = (char *) VIDMEM_ADDRESS;
    unsigned int i=0;
    unsigned int j=UPPER_SCREEN_SIZE;
    size_t length= strlen(str);
    while(i < length && j < MAIN_SCREEN_SIZE)
    {
        vidmem[j++]=str[i++];
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
    size_t len = 0;
    while(string[len] != 0){
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

char * tostring(char* str, int number)
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

void int_80h(unsigned int sysCallNumber, unsigned int arg1, int arg2, int arg3, int arg4, int arg5)
{
    switch(sysCallNumber){
        case SYS_WRITE:
          write((int)arg1, (void *)arg2, (size_t)arg3);
            break;
        case SYS_READ:
          read((int)arg1, (void *)arg2,(size_t)arg3);
	    break;
    }
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
