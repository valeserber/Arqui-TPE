#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"

extern int writepos;
extern BUFFER keyboard_buffer;

void shell_run(){

   int linepos=(keyboard_buffer.buffer_pos);
   printf("***>");
   while(linepos==(keyboard_buffer.buffer_pos)){
   }
   while(keyboard_buffer.buffer[(keyboard_buffer.buffer_pos)-1]!='\n'){
   }
   //searchCommand(linepos);
   while((writepos%160)!=0){
	writepos+=2;
   }
   //while(writepos%160!=0){
  // }
   
}

/* solo se admite un comando en una linea
void searchCommand(int linepos){
   while(keyboard_buffer[linepos]!='\n'){
	
        while(keyboard_buffer[linepos]!=' '){
        //armar un string
        }
        //checkear comando
        //despues vienen los argumentos


   }
}*/
