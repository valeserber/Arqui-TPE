#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"

SHELL shell_buffer;

int addToShellBuffer();
void initialize_shell();
void shell_run();


void shell_run(){
   int linepos=keyboardpos();
   int ans=0;
   max_pos(shell_buffer.shell_pos);
   initialize_shell();
   printf("***>");
   do{
       while(linepos==keyboardpos()){
       }
       ans=addToShellBuffer();
       max_pos(shell_buffer.shell_pos);
       linepos=keyboardpos();
   }while(ans!=ENTER);
   
}

void initialize_shell(){
   shell_buffer.shell_pos=0;
   int i;
   for(i=0;i<SHELL_SIZE;i++){
	shell_buffer.buffer[i]=0;
   }
}


int addToShellBuffer(){
   char * buf=(char *)keyboardbuffer();
   char key= buf[keyboardpos()-1];
   int i=0;
   switch(key){
	case '\n':
		  //searchCommand();
		  return ENTER;
		  break;
        case '\b':
                  if(shell_buffer.shell_pos>0){
			shell_buffer.buffer[--(shell_buffer.shell_pos)]=0;
                  }
		  break;
	case '\t':
                  while(i<TAB_LENGTH){
			  shell_buffer.buffer[(shell_buffer.shell_pos)++]=' ';
			  i++;
		  }
		  break;
	default:
	          shell_buffer.buffer[(shell_buffer.shell_pos)++]=key;
		  break;
   }
   return 0;
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
