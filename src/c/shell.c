#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"

SHELL shell_buffer;

void addToShellBuffer(char c);
void initialize_shell();
void shell_run();
bool shBufferIsEmpty();
bool shBufferIsFull();


void shell_run(){
  // int linepos=keyboardpos();
   //int ans=0;
   initialize_shell();
   max_pos(shell_buffer.shell_pos);
   printf("***>");
   
   while(1){
	char c=getchar();
	if(c!=EOF){
		putc((int)c,STDOUT);
 		if(c=='\n'){	
			//searchCommands();
			return;
		}
		else{
			addToShellBuffer(c);
               		max_pos(shell_buffer.shell_pos);
		}
   	}	   
   }
}

void initialize_shell(){
   shell_buffer.shell_pos=0;
   int i;
   for(i=0;i<SHELL_SIZE;i++){
	shell_buffer.buffer[i]=0;
   }
}


void addToShellBuffer(char c){
   int i=0;
   switch(c){
	case '\b':
        	if(!shBufferIsEmpty()){
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
        	if(!shBufferIsFull()){
       		    shell_buffer.buffer[(shell_buffer.shell_pos)++]=c;
       		}
		break;
   }
}

bool shBufferIsEmpty(){
    return shell_buffer.shell_pos == 0;
}

bool shBufferIsFull(){
    return shell_buffer.shell_pos == SHELL_SIZE;
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
