#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"

extern BUFFER keyboard_buffer;
void write(int fd, const void * buf, size_t count);
extern void writeToMainScreen(const void * buf,size_t count);
extern void scrollMainScreen();

int tickpos=640;

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
    char *b=(char *)buf;
    unsigned int i=0;    
    while(i<count){
    	char key= b[i++];
    	switch(key){
 		case '\n':
			 video_enter(fd);
			 break;
		case '\t':
			 video_tab(fd);
		         break;	
		case '\b':
		  	 video_backspace();
		 	 break;
		default:
			writeToScreen(key,fd);
			break;
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
