#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"


void shell_run(){

   int linepos=keyboardpos();
   printf("***>");
   while(linepos==keyboardpos()){
   }
   char * buf= (char *)keyboardbuffer();   
   while((buf[keyboardpos()-1])!='\n'){
   }
   //searchCommand(linepos);
   enter(STDOUT);

   
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
