#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"
#include "../../include/shell.h"

SHELL shell_buffer;
char * command[]={"openCD","infoCD","closeCD","clear"};

void shell_run(){
   initialize_shell();
   max_pos(shell_buffer.shell_pos);
   printf("***>");
   
   while(1){
	char c=getchar();
	if(c!=EOF){
		putc((int)c,STDOUT);
 		if(c=='\n'){	
			searchCommand();
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
	

void searchCommand(){
    char com[30];
    int i, j;

    for(i = 0; i < 30; i++){
        com[i] = 0;
    }
    for(i=0;i<shell_buffer.shell_pos;i++){
	com[i]=shell_buffer.buffer[i];
    }
    j=checkCommand(com);
    if(j!=-1){
	executeCommand(j);
    }
    else{
	printf("Invalid command\n");
    }       
}

int checkCommand(char * com){
    int i;
    for(i=0;i<COMMAND_SIZE;i++){printf("%s%s",command[i],com);
	if(strcmp(command[i],com)==0){
		return i;
	}
    }
    return -1;
}

void executeCommand(int c){
    switch(c){
	case 0:
		//openCD();
		break;
	case 1:
		//infoCD();
		break;
	case 2:
		//closeCD();
		break;
	case 3:
		clear();
		break;
    }
}
