#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"

extern BUFFER keyboard_buffer;
void write(int fd, const void * buf, size_t count);

int tickpos=640;
int writepos=0;
int upperWritepos = 0;

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

void int_80h(unsigned int sysCallNumber, unsigned int arg1, int arg2, int arg3, int arg4, int arg5){
    switch(sysCallNumber){
        case SYS_WRITE:
            write((int)arg1, (void *)arg2, (size_t)arg3);
            break;
        case SYS_READ:
            read((int)arg1, (void *)arg2,(size_t)arg3);
	    break;
    }
}

//TODO
void write(int fd, const void * buf, size_t count){
    char *vidmem;
    int size;
    char *b= (char *)buf;
    if(fd==STDOUT){
       vidmem= (char *)MAIN_SCREEN_ADDRESS;
       size= MAIN_SCREEN_SIZE;
       unsigned int i=0;
       while(i < count && writepos < size){
          vidmem[writepos++]=b[i++];
          vidmem[writepos++]=WHITE_TXT;
       }
       if(writepos == size){
          writepos = 0;
        }
    }else if(fd == 0){ //TODO 0 es la pantalla superior, ponerle alias
        vidmem= (char *)VIDMEM_ADDRESS;
        size= UPPER_SCREEN_SIZE;
        unsigned int i=0;
        while(i < count && upperWritepos < size){
            vidmem[upperWritepos++]=b[i++];
            vidmem[upperWritepos++]=WHITE_TXT;
        }
        if(upperWritepos == size){
           upperWritepos = 0;
        }
    }
}

ssize_t read(int fd, void *buf, size_t count){
//   char * b=(char *) buf;
//   int i;
//   int j=0; 
//   for(i=0; i<count;i++){
//	b[i]=keyboard_buffer[j++];	
//	if(j==BUFFER_SIZE){
//		j=0;
//	}
//   }
  
   return 0; //TODO stub
}
