/**********************
 kc.h
**********************/
#include "defs.h"

#ifndef _kc_
#define _kc_

#define WHITE_TXT 0x07 // Atributo de video. Letras blancas, fondo negro

/* Muestra la imagen de inicio */
void showSplashScreen();

/* Tiempo de espera */
void wait(int time);

/* Limpia la pantalla */
void k_clear_screen();

/*Imprime hola mundo */
void print_hello();

/*Imprime en pantalla*/
void print(char * str);

/*Longitud del string*/
size_t strlen(char * str);

/*Calcula cantidad de memoria*/
size_t get_memory();

/*Convierte de long a char* */
char * to_string(char * str, long number);

/* Inicializa la entrada del IDT */
void setup_IDT_entry (DESCR_INT *item, byte selector, dword offset,
        byte access, byte cero);

/*Convierte de scancode a codigo ascii*/
int scancodeToAscii(unsigned char scancode);

/*Inicializa el buffer de teclado*/
void buffer_initialize(BUFFER * buf);

/*Agrega al buffer lo ingresado por teclado*/
void addToKeyboardBuffer(char ascii_c);

char * tostring(char* str, int number);

#endif
