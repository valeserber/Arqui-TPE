#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/stdio.h"
void test();
void test1();
void test2();
void test3();
void test4();
void test5();
void test6();
extern writepos;

void test(){
  printf("\tTests\n");
  printf("test1\t  Prints letters when a timer tick interruption arrives\n");
  printf("test2\t  Prints \"*\" when a number is multiple of 5.Starts with 0 and adds 1 in each iteration\n");
  printf("test3\t  Tests scanf. Expects integer, and prints the income\n");
  printf("test4\t  Tests scanf. Expects string, and prints the income\n");
  printf("test5\t  Tests scanf. Expects hexadecimal number, and prints the income as a decimal number\n");
  printf("test6\t  Adds 1 to a set of variables and prints them\n");
}

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
	 			printf("*\t");
			}
			i++;
		}
  	}
  }
}

void test3(){
  int integer;
  scanf("%d", &integer);
  printf("\t%d\n",integer);
}

void test4(){
  char string[10]={0};
  scanf("%s",string);
  printf("\t%s\n",string);
}

void test5(){
  int num;
  scanf("%x",&num);
  printf("\t%d\n",num);
}

void test6(){
  char c;
  int v1=10;
  int v2=30;
  int v3=50;
  int v4=70;
  printf("Press n to get the set of variables or enter to leave\n");
  while(1){
	c=getchar();
	if(c!=EOF){
		if(c=='\n'){
                        printf("\n");
			return;
		}
		if(c=='n'){
			printf("v1:%d ",v1);
			printf("v2:%d ",v2);
			printf("v3:%d ",v3);
			printf("v4:%d\n",v4);
			v1+=1;
			v2+=1;
			v3+=1;
			v4+=1;
		}
  	}
  }

}

