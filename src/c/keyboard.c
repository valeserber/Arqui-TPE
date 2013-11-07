#include "../../include/kc.h"
#include "../../include/defs.h"
#include "../../include/keyboard.h"

BUFFER keyboard_buffer;
extern void _registerInfo();
int keyboardpos();
unsigned char * keyboardbuffer();

int normal_keyboard[KEYS] = {
        //MAKECODE
	/*0x00*/                NOTHING,
        /*0x01*/ /*Esc*/        NOTHING,
        /*0x02*/                '1',        
        /*0x03*/                '2',        
        /*0x04*/                '3',        
        /*0x05*/                '4',        
        /*0x06*/                '5',        
        /*0x07*/                '6',        
        /*0x08*/                '7',        
        /*0x09*/                '8',        
        /*0x0A*/                '9',        
        /*0x0B*/                '0',        
        /*0x0C*/                '-',        
        /*0x0D*/                '=',        
        /*0x0E*/ /*Backspace*/  '\b',
        /*0x0F*/ /*Tab*/      	'\t',
        /*0x10*/                'q',        
        /*0x11*/                'w',        
        /*0x12*/                'e',        
        /*0x13*/                'r',        
        /*0x14*/                't',        
        /*0x15*/                'y',        
        /*0x16*/                'u',        
        /*0x17*/                'i',        
        /*0x18*/                'o',        
        /*0x19*/                'p',        
        /*0x1A*/                '[',        
        /*0x1B*/                ']',        
        /*0x1C*/ /*Enter*/      '\n',
        /*0x1D*/ /*Ctrl*/       CONTROL_MAKE,
        /*0x1E*/                'a',        
        /*0x1F*/                's',        
        /*0x20*/                'd',        
        /*0x21*/                'f',        
        /*0x22*/                'g',        
        /*0x23*/                'h',        
        /*0x24*/                'j',        
        /*0x25*/                'k',        
        /*0x26*/                'l',        
        /*0x27*/                ';',              
        /*0x28*/                '\'',        
        /*0x29*/                '`',        
        /*0x2A*/ /*Left shift*/ LEFT_SHIFT_MAKE,
        /*0x2B*/                '\\',    
        /*0x2C*/                'z',        
        /*0x2D*/                'x',        
        /*0x2E*/                'c',        
        /*0x2F*/                'v',        
        /*0x30*/                'b',        
        /*0x31*/                'n',        
        /*0x32*/                'm',        
        /*0x33*/                ',',      
        /*0x34*/                '.',        
        /*0x35*/                '/',        
        /*0x36*/ /*Right shift*/RIGHT_SHIFT_MAKE,
        /*0x37*/ /*Keypad*/     '*',            
        /*0x38*/ /*Left alt*/   NOTHING,
        /*0x39*/                ' ',
        /*0x3A*/ /*Caps Lock*/  CAPS_LOCK,
        /*0x3B*/ /*F1*/         NOTHING, 
        /*0x3C*/ /*F2*/         NOTHING,
        /*0x3D*/ /*F3*/         NOTHING,
        /*0x3E*/ /*F4*/         NOTHING,
        /*0x3F*/ /*F5*/         NOTHING,
        /*0x40*/ /*F6*/         NOTHING,
        /*0x41*/ /*F7*/         NOTHING,
        /*0x42*/ /*F8*/         NOTHING,
        /*0x43*/ /*F9*/         NOTHING,
        /*0x44*/ /*F10*/        NOTHING,
        /*0x45*/ /*Num lock*/   NOTHING,
        /*0x46*/ /*Scroll lock*/NOTHING,
        /*0x47*/ /*Up arrow*/   NOTHING,
        /*0x48*/                NOTHING,
        /*0x49*/                NOTHING,
        /*0x4A*/                NOTHING,
        /*0x4B*/ /*Left arrow*/ 0x4b * 2,
        /*0x4C*/                NOTHING,
        /*0x4D*/ /*Right arrow*/0x4d * 2,
        /*0x4E*/                NOTHING,
        /*0x4F*/                NOTHING,
        /*0x50*/ /*Down arrow*/ NOTHING,
        /*0x51*/                NOTHING,
        /*0x52*/                NOTHING,
        /*0x53*/ /*Delete*/     NOTHING,
        /*0x54*/                NOTHING,
        /*0x55*/                '+',        
        /*0x56*/                '+',
        /*0x57*/ /*F11*/        NOTHING,
        /*0x58*/ /*F12*/        NOTHING};


int special_keyboard[KEYS] = {
        //MAKECODE
	/*0x00*/                NOTHING,
        /*0x01*/ /*Esc*/        NOTHING,
        /*0x02*/                '!',        
        /*0x03*/                '@',        
        /*0x04*/                '#',        
        /*0x05*/                '$',        
        /*0x06*/                '%',        
        /*0x07*/                '^',        
        /*0x08*/                '&',        
        /*0x09*/                '*',        
        /*0x0A*/                '(',        
        /*0x0B*/                ')',        
        /*0x0C*/                '_',        
        /*0x0D*/                '+',        
        /*0x0E*/ /*Backspace*/  '\b',
        /*0x0F*/ /*Tab*/        '\t',
        /*0x10*/                'Q',        
        /*0x11*/                'W',        
        /*0x12*/                'E',        
        /*0x13*/                'R',        
        /*0x14*/                'T',        
        /*0x15*/                'Y',        
        /*0x16*/                'U',        
        /*0x17*/                'I',        
        /*0x18*/                'O',        
        /*0x19*/                'P',        
        /*0x1A*/                '{',        
        /*0x1B*/                '}',        
        /*0x1C*/ /*Enter*/      '\n',
        /*0x1D*/ /*Ctrl*/       CONTROL_MAKE,
        /*0x1E*/                'A',        
        /*0x1F*/                'S',        
        /*0x20*/                'D',        
        /*0x21*/                'F',        
        /*0x22*/                'G',        
        /*0x23*/                'H',        
        /*0x24*/                'J',        
        /*0x25*/                'K',        
        /*0x26*/                'L',        
        /*0x27*/                ':',                
        /*0x28*/                '"',        
        /*0x29*/                '~',        
        /*0x2A*/ /*Left shift*/ NOTHING,
        /*0x2B*/                '|',        
        /*0x2C*/                'Z',        
        /*0x2D*/                'X',        
        /*0x2E*/                'C',        
        /*0x2F*/                'V',        
        /*0x30*/                'B',        
        /*0x31*/                'N',        
        /*0x32*/                'M',        
        /*0x33*/                '<',        
        /*0x34*/                '>',        
        /*0x35*/                '?',        
        /*0x36*/ /*Right shift*/NOTHING,
        /*0x37*/                '*',            
        /*0x38*/ /*Left alt*/   NOTHING,
        /*0x39*/                ' ',
        /*0x3A*/ /*Caps Lock*/  NOTHING,
        /*0x3B*/ /*F1*/         NOTHING, 
        /*0x3C*/ /*F2*/         NOTHING,
        /*0x3D*/ /*F3*/         NOTHING,
        /*0x3E*/ /*F4*/         NOTHING,
        /*0x3F*/ /*F5*/         NOTHING,
        /*0x40*/ /*F6*/         NOTHING,
        /*0x41*/ /*F7*/         NOTHING,
        /*0x42*/ /*F8*/         NOTHING,
        /*0x43*/ /*F9*/         NOTHING,
        /*0x44*/ /*F10*/        NOTHING,
        /*0x45*/ /*Num lock*/   NOTHING,
        /*0x46*/ /*Scroll lock*/NOTHING,
        /*0x47*/ /*Up arrow*/   NOTHING,
        /*0x48*/                NOTHING,
        /*0x49*/   	        NOTHING,
        /*0x4A*/                NOTHING,
        /*0x4B*/ /*Left arrow*/ 0x4b * 2,
        /*0x4C*/                NOTHING,
        /*0x4D*/ /*Right arrow*/0x4d * 2,
        /*0x4E*/                NOTHING,
        /*0x4F*/                NOTHING,
        /*0x50*/ /*Down arrow*/ NOTHING,
        /*0x51*/                NOTHING,
        /*0x52*/                NOTHING,
        /*0x53*/ /*Delete*/     NOTHING,
        /*0x54*/                NOTHING,
        /*0x55*/                '*',        
        /*0x56*/                '*',        
        /*0x57*/ /*F11*/        NOTHING,
        /*0x58*/ /*F12*/        NOTHING};

int scancodeToAscii(unsigned char scancode){
    if(scancode & 0x80){ 
	if((scancode==LEFT_SHIFT_BREAK)||(scancode==RIGHT_SHIFT_BREAK)){
		keyboard_buffer.flag.shiftOn=false;
	}else if(scancode==CONTROL_BREAK){
		keyboard_buffer.flag.controlOn=false;
	}
	return 0;
    }
    if(scancode==CONTROL_R){
	if(keyboard_buffer.flag.controlOn==true){		
		clearRegisters();
		reset_upperWritepos();
		_registerInfo();		
		return 0;
	}
    }
 
    int key= normal_keyboard[scancode];
    switch(key){
	case CONTROL_MAKE:
	    keyboard_buffer.flag.controlOn = true;
		return 0;
		break;
	case CAPS_LOCK:
	    keyboard_buffer.flag.capsLockOn = !keyboard_buffer.flag.capsLockOn;
                return 0;
		break;
	case LEFT_SHIFT_MAKE:
	case RIGHT_SHIFT_MAKE:
	    keyboard_buffer.flag.shiftOn= true;
		return 0;
		break;
	default:
		if(keyboard_buffer.flag.capsLockOn ||
		   keyboard_buffer.flag.shiftOn){
			key=special_keyboard[scancode];
		}
		break;	
    }	
    return key;
}

void buffer_initialize(){
    int i;
    keyboard_buffer.enqueuePos = keyboard_buffer.dequeuePos = 0;
   
    for( i = 0; i < BUFFER_SIZE; i++){
        keyboard_buffer.buffer[i] = 0;
    }
    keyboard_buffer.flag.shiftOn=false;
    keyboard_buffer.flag.controlOn=false;
    keyboard_buffer.flag.capsLockOn=false;
}

bool kbBufferIsEmpty(void){
    return keyboard_buffer.enqueuePos == keyboard_buffer.dequeuePos;
}

bool kbBufferIsFull(void){
    return keyboard_buffer.enqueuePos == keyboard_buffer.dequeuePos-1;
}

bool addToKeyboardBuffer(unsigned char ascii_c){
    if(kbBufferIsFull()) return false; // Se podria agregar un pitido a la motherboard :)
   keyboard_buffer.buffer[keyboard_buffer.enqueuePos] = ascii_c;
   keyboard_buffer.enqueuePos = (keyboard_buffer.enqueuePos + 1) % BUFFER_SIZE;
}

int kbBufferGetNext(){
    if(kbBufferIsEmpty()) return -1;
    int dequeuePos = keyboard_buffer.dequeuePos;
    keyboard_buffer.dequeuePos = (keyboard_buffer.dequeuePos +1) % BUFFER_SIZE;
    return keyboard_buffer.buffer[dequeuePos];

}

int keyboardpos(void){
   return keyboard_buffer.enqueuePos;
}

unsigned char * keyboardbuffer(void){
   return keyboard_buffer.buffer;
}

