
/*Sets a character that the int08 handler will print later*/
void set_char(char ch);

/*Timmer tick interruption*/
void int_08();

/*Keyboard interruption*/
void int_09(unsigned char scancode);

/*Int 80h interruption*/
void int_80h(dword sysCallNumber, dword arg1,dword arg2,
             dword arg3,dword arg4, int arg5);
