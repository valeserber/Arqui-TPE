/***************************************************
  defs.h

****************************************************/

#ifndef _defs_
#define _defs_

#define MAX_MEMORY          0x01100000
#define TWO_MB              2097152
#define INITIAL_MEM         0x00200000
#define VIDMEM_ADDRESS      0xb8000
#define CHAR_SIZE           2
#define SCREEN_COLS         80
#define MAIN_SCREEN_ADDRESS 0xb8640
#define MAIN_SCREEN_ROWS    15
#define MAIN_SCREEN_SIZE    SCREEN_COLS*MAIN_SCREEN_ROWS*CHAR_SIZE
#define UPPER_SCREEN_ROWS   10
#define UPPER_SCREEN_SIZE   SCREEN_COLS*UPPER_SCREEN_ROWS*CHAR_SIZE
#define INT_MIN             (-2147483647-1)
#define BUFFER_SIZE	    256
#define KEYS		    89
#define NOTHING		    0
#define SYS_READ 	    3
#define SYS_WRITE 	    4
#define LEFT_SHIFT_MAKE     257
#define RIGHT_SHIFT_MAKE    258
#define CAPS_LOCK           259
#define LEFT_SHIFT_BREAK    0xAA
#define RIGHT_SHIFT_BREAK   0xB6
#define CONTROL_MAKE	    260
#define CONTROL_R     	    0x13
#define CONTROL_BREAK	    0x9D
#define LAST_LINE	    14*80*2
#define LINE_SIZE	    80*2
#define TAB_LENGTH          8
#define SHELL_SIZE          128
#define ENTER	            261
#define PROMPT_LENGTH       4
/*
 * Type definitions
 */
typedef unsigned char byte;
typedef short int word;
typedef int dword;
typedef unsigned int size_t;
typedef signed int ssize_t;
typedef enum {false, true} bool;

/* Flags para derechos de acceso de los segmentos */
#define ACS_PRESENT     0x80            /* segmento presente en memoria */
#define ACS_CSEG        0x18            /* segmento de codigo */
#define ACS_DSEG        0x10            /* segmento de datos */
#define ACS_READ        0x02            /* segmento de lectura */
#define ACS_WRITE       0x02            /* segmento de escritura */
#define ACS_IDT         ACS_DSEG
#define ACS_INT_386     0x0E            /* Interrupt GATE 32 bits */
#define ACS_INT         ( ACS_PRESENT | ACS_INT_386 )

#define ACS_CODE        (ACS_PRESENT | ACS_CSEG | ACS_READ)
#define ACS_DATA        (ACS_PRESENT | ACS_DSEG | ACS_WRITE)
#define ACS_STACK       (ACS_PRESENT | ACS_DSEG | ACS_WRITE)

#pragma pack (1)        /* Alinear las siguiente estructuras a 1 byte */

/* Segment descriptor */
typedef struct {
  word limit,
       base_l;
  byte base_m,
       access,
       attribs,
       base_h;
} DESCR_SEG;


/* Descriptor de interrupcion */
typedef struct {
  word      offset_l,
            selector;
  byte      cero,
            access;
  word      offset_h;
} DESCR_INT;

/* IDTR */
typedef struct {
  word  limit;
  dword base;
} IDTR;

typedef struct{
  int fd;
  size_t size;
  char * buffer;
} FILE;

typedef struct{
    unsigned int shiftOn    : 1;
    unsigned int controlOn  : 1;
    unsigned int capsLockOn : 1;
} flags;

typedef struct{
  unsigned char buffer[BUFFER_SIZE];
  int enqueuePos;//buffer_pos;
  int dequeuePos;
  flags flag;
} BUFFER;

typedef struct{
  unsigned char buffer[SHELL_SIZE];
  int shell_pos;
}SHELL;
#endif
