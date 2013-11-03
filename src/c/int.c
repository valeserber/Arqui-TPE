#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"

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

//TODO
void write(int fd, const void * buf, size_t count){
    char *vidmem;
    int size;
    if(fd==STDIN){
       vidmem= (char *)MAIN_SCREEN_ADDRESS;
       size= MAIN_SCREEN_SIZE;
       char *b= (char *)buf;
       unsigned int i=0;
       while(i < count && writepos < size){
          vidmem[writepos++]=b[i++];
          vidmem[writepos++]=WHITE_TXT;
       }
       if(writepos == size){
          writepos = 0;
       }
    }
    else{
       vidmem= (char *)VIDMEM_ADDRESS;
       size= UPPER_SCREEN_SIZE;
       //write_registers(vidmem,size);
    }
    
}

ssize_t read(int fd, const void *buf, size_t count){
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
