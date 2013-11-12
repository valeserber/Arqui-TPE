#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"
#include "../../include/shell.h"
#include "../../include/keyboard.h"
#include "../../include/video.h"

SHELL shell_buffer;
char * command[]={"openCD","infoCD","closeCD","clear","test","help","clearUp","test1","test2","test3","test4","test5","test6","test7"};
extern _opencd();
extern _infocd();
extern _closecd();
int printNum(int num);
int printStatus(int num);

void shell_run(){
    initialize_shell();
    max_pos(shell_buffer.shell_pos);
    printf("***>");
    paintLetter(LILAC_TXT);
    set_cursor(get_row(),4);

    while(1){
        char c=getchar();
        if(c!=EOF){
            if(c=='\n'){
                putc((int)c,STDOUT);
                searchCommand();
                return;
            }else{
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
	    if(strcmp(command[i],com)==0) return i;
    }
    return -1;
}

void executeCommand(int c){
    switch(c){
    case 0:
        _opencd();
        break;
    case 1:
        _infocd();
        break;
    case 2:
        _closecd();
        break;
    case 3:
        clear();
        break;
    case 4:
        test();
        break;
    case 5:
        help();
        break;
    case 6:
        clearRegisters();
        break;
    case 7:
        test1();
        break;
    case 8:
        test2();
        break;
    case 9:
        test3();
        break;
    case 10:
        test4();
        break;
    case 11:
        test5();
        break;
    case 12:
        test6();
        break;
    }
}

void help(){
    printf("\tCommands\n"); //agregar que hace cada cosa
    printf("openCD\t Opens disk tray\n");
    printf("infoCD\t Reads the CD info\n");
    printf("closeCD\tCloses disk tray\n");
    printf("clear\t  Clears the main screen\n");
    printf("clearUp\tClears the upper screen\n");
    printf("test\t   Lists available tests\n");
    printf("help\t   Lists available commands\n");
    printf("\tShortcuts\n");
    printf("Ctrl+R:  Shows the value of the registers at the time the keys were pressed\n");
}

void printCapacity(unsigned int lba, unsigned int blockLength){
    printf("Capacity = %d", (lba+1)*blockLength);
}

