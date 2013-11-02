#include "../../include/kc.h"
#include "../../include/defs.h"

extern BUFFER keyboard_buffer;

int tickpos=640;
int writepos=0;

void int_08(){
    char *video = (char *)0xb8000;
    video[tickpos+=2]='*';
}

void int_09(unsigned char scancode){
    //dsp borrar esta linea
    char *vidmem = (char *) VIDMEM_ADDRESS;
    
    _Cli();
    int ascii_c = scancodeToAscii(scancode);
    
    if(ascii_c !=0){
      // putc(ascii_c,1);
       addToKeyboardBuffer(ascii_c);
      //esto es para imprimir, dsp hay que borrarlo
        int j;
	char i=0;
	for(j=0; j< BUFFER_SIZE; j++,i++){
 	vidmem[j++]=keyboard_buffer.buffer[i++];
        vidmem[j]=WHITE_TXT;
       //hasta aca
	}
	
    }
    _Sti();
}

//TODO
void write(int fd, const void * buf, size_t count){
    char *vidmem = (char *)MAIN_SCREEN_ADDRESS;
    unsigned int i=0;
    while(i < count && writepos < MAIN_SCREEN_SIZE){
        vidmem[writepos++]=((char *)buf)[i++];
        vidmem[writepos++]=WHITE_TXT;
    }
    if(writepos == MAIN_SCREEN_SIZE){
        writepos = 0;
    }
}
