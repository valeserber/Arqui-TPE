#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"
void test1();
void test2();
extern writepos;

void test1(){
  _Cli();
  char c1='s';
  char c2='a';
  char c3='i';
  set_char(c1);
  _mascaraPIC1(0xFC); //habilita teclado y timer tick
  _Sti();
  while(writepos<80*5*2){
  }
  set_char(c2);
  while(writepos<80*10*2){
  }
  set_char(c3);
  while(writepos<80*15*2){
  }
	
  _Cli();
  _mascaraPIC1(0xFD);//queda habilitado solo el teclado
  _Sti();
}

void test2(){
  int i=0;
  char c;
  printf("Press n to get the next number or enter to leave\n");
  while(1){
	c=getchar();
	if(c!=EOF){
		if(c=='\n'){
                        printf("\n");
			return;
		}
		if(c=='n'){
			if(i%5==0){
	 			printf("modulo5\t");
			}
			i++;
		}
  	}
  }
}



