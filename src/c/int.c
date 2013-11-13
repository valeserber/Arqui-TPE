#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"
#include "../../include/keyboard.h"

char c='*';

void int_08(){
    char *video = (char *)MAIN_SCREEN_ADDRESS;
    putchar(c);
}

void set_char(char ch){
    c=ch;
}

void int_09(unsigned char scancode){
    _Cli();
    int ascii_c = scancodeToAscii(scancode);
    if(ascii_c !=0){
       putc(ascii_c,STDIN);
    }
    _Sti();
}

void int_80h(dword sysCallNumber, dword arg1, dword arg2, dword arg3, 
             dword arg4, dword arg5){
    _Sti();
    switch(sysCallNumber){
        case SYS_WRITE:
            __write((int)arg1, (void *)arg2, (size_t)arg3);
            break;
        case SYS_READ:
            __read((int)arg1, (void *)arg2,(size_t)arg3);
	    break;
    }
}

ssize_t __write(int fd, const void * buf, size_t count){
    unsigned int i=0;    
    while(i<count){
	char key= ((char*)buf)[i++];
	if(fd==STDIN){
		addToKeyboardBuffer(key);
	}
	else if(fd==STDOUT || fd==REGOUT){
		video_write(key,fd);
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
	        readCharacters++;
            }
	}
    }
    return readCharacters;
}
