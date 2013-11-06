#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"
void test1();
extern writepos;

void test1(){
  _Cli();
  _mascaraPIC1(0xFC); //habilita teclado y timer tick
  _Sti();

  int c1='s';
  int c2='a';
  int c3='i';
  
  set_char(c1);
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

