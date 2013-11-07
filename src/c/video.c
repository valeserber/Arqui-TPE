#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"
void writeToScreen(char key, int fd);
void scrollMainScreen();
void clearLine(char * vidmem);
void clearRegisters();
void video_enter(int fd);
void video_backspace();
void video_tab(int fd);
void insertKey(char key, int * pos, char * vid);
void max_pos(int max);
void reset_upperWritepos();

int writepos=0;
int upperWritepos = 0;
char *vidmem= (char *)MAIN_SCREEN_ADDRESS;
int maxpos=0;

void writeToScreen(char key,int fd){
    int size;
    int * pos;
    if(fd==STDOUT){
	vidmem=(char *)MAIN_SCREEN_ADDRESS;
    	size= MAIN_SCREEN_SIZE;
        if(writepos == size){  
		scrollMainScreen();
    	}
	insertKey(key,&writepos,vidmem); 
    }
    else if(fd==REGOUT){
	vidmem=(char *)VIDMEM_ADDRESS;
    	size= UPPER_SCREEN_SIZE-LINE_SIZE;
    	
        if(upperWritepos == size){
	 // return;         
	//no se que deberia hacer
         upperWritepos = 0;
    	}
	insertKey(key,&upperWritepos,vidmem);
    }
}

void reset_upperWritepos(){
	upperWritepos=0;
}

void insertKey(char key, int * pos, char * vid){
    vid[(*pos)]=key;
    (*pos)++;
    vid[(*pos)]=WHITE_TXT; 
    (*pos)++;
}

void scrollMainScreen(){
    vidmem= (char *) MAIN_SCREEN_ADDRESS;
    int i=LINE_SIZE;   
    writepos=0; 
    while(i<MAIN_SCREEN_SIZE){
	vidmem[writepos++]=vidmem[i++];
    }
    clearLine((char *)LAST_LINE_ADDRESS);
    writepos=LAST_LINE;
}

void clearLine(char * vidmem){
    int i=0;
    while(i<LINE_SIZE){
	vidmem[i++]=' ';
	vidmem[i++]=WHITE_TXT;
    }
}

void clear(){
   int line;
   for(line=10;line<MAIN_SCREEN_ROWS;line++){
	clearLine((char *)MAIN_SCREEN_ADDRESS);
   }
}

void clearRegisters(){
   int line;
   for(line=0;line<UPPER_SCREEN_ROWS-1;line++){
	clearLine((char *)(VIDMEM_ADDRESS)+(LINE_SIZE*line));
   }
}

void video_write(char c,int fd){

    switch(c){
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
			writeToScreen(c,fd);
			break;
    }
}

void video_enter(int fd){
   if(fd==STDOUT){
  	while((writepos%160)!=0){
		writepos+=2;
   	}
	if(writepos == MAIN_SCREEN_SIZE){  
		scrollMainScreen();
        }
   }
   else if(fd==REGOUT){
	while((upperWritepos%160)!=0){
		upperWritepos+=2;
	}
   }
}

void video_backspace(){
   vidmem=(char *)MAIN_SCREEN_ADDRESS;
   if(maxpos>0){
	vidmem[--writepos]=WHITE_TXT;
	vidmem[--writepos]=' ';
   }
}

void max_pos(int max){
   maxpos=max;
}

void video_tab(int fd){
  
   int i=0;
   int size=0;
   int * pos;
   if(fd==STDOUT){
   	 vidmem=(char *)MAIN_SCREEN_ADDRESS;
         size=MAIN_SCREEN_SIZE;
         pos=&writepos;
   }
   else if(fd==REGOUT){
         vidmem=(char *)VIDMEM_ADDRESS;
	 size=UPPER_SCREEN_SIZE;
	 pos=&upperWritepos;
   }
   for(i=0; i<TAB_LENGTH && i<size; i++){
	insertKey(' ',pos, vidmem);
   }
}

/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/

void k_clear_screen()
{
    char *vidmem = (char *) VIDMEM_ADDRESS;
    unsigned int i=0;
    while(i < UPPER_SCREEN_SIZE-LINE_SIZE){
        vidmem[i++]=' ';
        vidmem[i++]=WHITE_TXT;
    };
    while(i<UPPER_SCREEN_SIZE){
        vidmem[i++]=' ';
        vidmem[i++]=WHITE_SQUARE;
    }
    while(i < MAIN_SCREEN_SIZE){
        vidmem[i++]=' ';
        vidmem[i++]=WHITE_TXT;
    };
}
