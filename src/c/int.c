#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"
#include "../../include/keyboard.h"

extern BUFFER keyboard_buffer;
ssize_t __write(int fd, const void * buf, size_t count);
ssize_t __read(int fd, void *buf, size_t count);
extern void writeToMainScreen(const void * buf,size_t count);
extern void scrollMainScreen();

char c='*';

int tickpos=0;

void int_08(){
    char *video = (char *)MAIN_SCREEN_ADDRESS;
   // video[tickpos+=2]='*';
    putchar(c);
}

void set_char(char ch){
    c=ch;
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
            __write((int)arg1, (void *)arg2, (size_t)arg3);
            break;
        case SYS_READ:
            __read((int)arg1, (void *)arg2,(size_t)arg3);
	    break;
    }
}

//TODO
ssize_t __write(int fd, const void * buf, size_t count){
    unsigned int i=0;    
    while(i<count){
    	char key= ((char*)buf)[i++];
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
    return i;
}

ssize_t __read(int fd, void *buf, size_t count){
    int readCharacters = 0;
    if(fd == STDIN){
        int aux;
        while(readCharacters < count){
	    if((aux = kbBufferGetNext()) != -1){
                ((char*)buf)[readCharacters] = aux;
            }
	    readCharacters++;
	}
    }
    return readCharacters;
}
