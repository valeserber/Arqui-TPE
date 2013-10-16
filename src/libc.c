#include "../include/kc.h"
#define MAX_MEMORY 0x01100000
#define TWO_MB 2097152
#define INITIAL_MEM 0x00200000

/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen() 
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	while(i < (80*25*2))
	{
		vidmem[i]='-';
		i++;
		vidmem[i]=WHITE_TXT;
		i++;
	};
}

/***************************************************************
*print_hello
*
* Imprime hola mundo en pantalla en modo texto color.
****************************************************************/

void print_hello() 
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	unsigned int j=80*15*2;
	char *string = "Hola mundo";
	while(j < (80*15*2)+20)
	{
		vidmem[j]=string[i];
		i++;
		j++;
		vidmem[j]=WHITE_TXT;
		j++;
	};
}

/***************************************************************
*print
*
* Imprime en pantalla en modo texto color.
****************************************************************/

void print(char * string) 
{
	char *vidmem = (char *) 0xb8000;
	unsigned int i=0;
	unsigned int j=0;
	long length= str_length(string);
	while(i < length && j<80*25*2)
	{
		vidmem[j]=string[i];
		i++;
		j++;
		vidmem[j]=WHITE_TXT;
		j++;
	}
}

/***************************************************************
*str_length
*
* Devuelve la longitud del string.
****************************************************************/

long str_length(char * string) 
{
	long length=0;
	while(string[length]!='\0'){
		length++;
	}
	return length;
}

/***************************************************************
*get_memory
*
* Calcula la cantidad de memoria comenzando en 2MB.
****************************************************************/

long get_memory() 
{
	long bytes=TWO_MB;
	int * mem= (int *)INITIAL_MEM;
	while(mem< (int *)MAX_MEMORY){
		*mem=67;
		if(*mem==67){
			*mem=142;
			if(*mem==142){
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
		number= number/10;
	}
	string[i]=0;
	int stop=i;
	int k=0;
	i--;
	while(i>=stop/2){
		char aux= string[k];
		string[k]=string[i];
		string[i]=aux;
		k++;
		i--;
	}	
	return string;
}
/***************************************************************
*setup_IDT_entry
* Inicializa un descriptor de la IDT
*
*Recibe: Puntero a elemento de la IDT
*	 Selector a cargar en el descriptor de interrupcion
*	 Puntero a rutina de atencion de interrupcion	
*	 Derechos de acceso del segmento
*	 Cero
****************************************************************/

void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset, byte access,
			 byte cero) {
  item->selector = selector;
  item->offset_l = offset & 0xFFFF;
  item->offset_h = offset >> 16;
  item->access = access;
  item->cero = cero;
}
