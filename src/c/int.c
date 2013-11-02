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
    _Cli();
    int ascii_c = scancodeToAscii(scancode);
    
    if(ascii_c !=0){
       putc(ascii_c,1);
       addToKeyboardBuffer(ascii_c);
    }
    _Sti();
}

//TODO
void write(int fd, const void * buf, size_t count){
    char *vidmem = (char *)MAIN_SCREEN_ADDRESS;
    char *b= (char *)buf;
    unsigned int i=0;
    while(i < count && writepos < MAIN_SCREEN_SIZE){
        vidmem[writepos++]=b[i++];
        vidmem[writepos++]=WHITE_TXT;
    }
    if(writepos == MAIN_SCREEN_SIZE){
        writepos = 0;
    }
}
