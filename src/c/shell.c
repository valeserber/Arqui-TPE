#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"
#include "../../include/shell.h"
#include "../../include/keyboard.h"
#include "../../include/video.h"

SHELL shell_buffer;
char * command[]={"openCD","infoCD","closeCD","clear","test1","test2","help","clearUp"};
extern _opencd();
int printNum(int num);
int printStatus(int num);
void shell_run(){
   initialize_shell();
   max_pos(shell_buffer.shell_pos);
   printf("***>");
   paintLetter(LILAC_TXT);
   set_cursor(getrow(),4);

   while(1){
	char c=getchar();
	if(c!=EOF){
 		if(c=='\n'){
			putc((int)c,STDOUT);	
			searchCommand();
			return;
		}
		else{
			if(addToShellBuffer(c)){
				putc((int)c,STDOUT);
			}
			
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


bool addToShellBuffer(char c){
   int i=0;
   switch(c){
	case '\b':
        	if(!shBufferIsEmpty()){
        	    shell_buffer.buffer[--(shell_buffer.shell_pos)]=0;
		    return true;
       		}
		break;
   	case '\t':
        	while(i<TAB_LENGTH){
		    shell_buffer.buffer[(shell_buffer.shell_pos)++]=' ';
	            i++;
		}
                return true;
	        break;
	default:
        	if(!shBufferIsFull()){
       		    shell_buffer.buffer[(shell_buffer.shell_pos)++]=c;
		    return true;
       		}
		break;
   }
   return false;
}

bool shBufferIsEmpty(){
    return shell_buffer.shell_pos == 0;
}

bool shBufferIsFull(){
    return shell_buffer.shell_pos == SHELL_SIZE;
}
	

void searchCommand(){
    char com[300];
    int i, j;

    if(shBufferIsEmpty()){
	return;
    }
    for(i = 0; i < 300; i++){
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
    for(i=0;i<COMMAND_SIZE;i++){
	if(strcmp(command[i],com)==0){
		return i;
	}
    }
    return -1;
}

void executeCommand(int c){
    switch(c){
	case 0:
		_opencd();
		break;
	case 1:
		//infoCD();
		break;
	case 2:
		_closecd();
		break;
	case 3:
		clear();
		break;
	case 4:
		test1();
		break;
	case 5:
		test2();
		break;
	case 6:
		help();
		break;
	case 7:
		clearRegisters();
		break;
    }
}

void help(){
  printf("Commands\n"); //agregar que hace cada cosa
  printf("openCD\t\n");
  printf("infoCD\t\n");
  printf("closeCD\t\n");
  printf("clear\tClears the main screen\n");
  printf("clearUp\tClears the upper screen\n");
  printf("test1\tPrints letters when a timer tick interruption arrives\n");
  printf("test2\tPrints \n");
  printf("help\tLists available commands\n");
  printf("Shortcuts\n");
  printf("Ctrl+R: \n");
}

int printStatus(int num){
int flag = 0;

// if((num & 0) == 0){
// printf("No flags ");
// }


if((num & 2) == 2){
printf("IDX ");
flag = 1;
}

if((num & 4) == 4){
printf("Corr ");
flag = 1;
}

if((num & 8) == 8){
printf("DRQ ");
flag = 1;
}

if((num & 16) == 16){
printf("DSC ");
flag = 1;
}

if((num & 32) == 32){
printf("DF ");
flag = 1;
}

if((num & 64) == 64){
printf("DRDY ");
flag = 1;
}

if((num & 128) == 128){
printf("BSY ");
flag = 1;
}

if(flag == 0){
printf("No flags ");
}

if((num & 1) == 1){
printf("Error: ");
_printError();

flag = 1;
}

printf("\n");



return 0;
}

int printNum(int num){
        printf("%d",num);
}



