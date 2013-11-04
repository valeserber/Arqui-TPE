#include "../../include/kc.h"
#include "../../include/defs.h"
void writeToMainScreen(const void * buf,size_t count);
void scrollMainScreen();
void clearLine(int initial,int size);
void clearRegisters();

int writepos=0;
int upperWritepos = 0;
char *vidmem= (char *)MAIN_SCREEN_ADDRESS;

void writeToMainScreen(const void * buf,size_t count){
    char *b= (char *)buf;
    int size= MAIN_SCREEN_SIZE;
    unsigned int i=0;
    while(i < count && writepos < size){
         vidmem[writepos++]=b[i++];
         vidmem[writepos++]=WHITE_TXT;
    }
    if(writepos == size){        
	scrollMainScreen();
    }
}

void scrollMainScreen(){
    int i=(SCREEN_COLS)*2;   
    writepos=0; 
    while(i<MAIN_SCREEN_SIZE){
	vidmem[writepos++]=vidmem[i++];
    }
    clearLine(LAST_LINE,MAIN_SCREEN_SIZE);
    writepos=LAST_LINE;
}

void clearLine(int initial,int size){
    while(initial<size){
	vidmem[initial++]=' ';
	vidmem[initial++]=WHITE_TXT;
    }
}

void clear(){
   int line;
   for(line=10;line<MAIN_SCREEN_ROWS;line++){
	clearLine(line,LINE_SIZE);
   }
}

void clearRegisters(){
   int line;
   for(line=0;line<UPPER_SCREEN_SIZE-1;line++){
	clearLine(line,LINE_SIZE);
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
