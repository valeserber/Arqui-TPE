#define BUFFER_SIZE	    256
#define KEYS		    89
#define NOTHING		    0
#define LEFT_SHIFT_MAKE     257
#define RIGHT_SHIFT_MAKE    258
#define CAPS_LOCK           259
#define LEFT_SHIFT_BREAK    0xAA
#define RIGHT_SHIFT_BREAK   0xB6
#define CONTROL_MAKE	    260
#define CONTROL_R     	    0x13
#define CONTROL_BREAK	    0x9D
#define TAB_LENGTH          8

/*Convierte de scancode a codigo ascii*/
int scancodeToAscii(unsigned char scancode);

/*Agrega al buffer lo ingresado por teclado*/
bool addToKeyboardBuffer(unsigned char ascii_c);

/*Inicializa el buffer de teclado*/
void buffer_initialize(void);

bool kbBufferIsEmpty(void);

bool kbBufferIsFull(void);

int  kbBufferGetNext(void);

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
