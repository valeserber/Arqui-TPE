
extern void writeToMainScreen(const void * buf,size_t count);
extern void scrollMainScreen();
void set_char(char ch);
void int_08();
void int_09(unsigned char scancode);
void int_80h(unsigned int sysCallNumber, unsigned int arg1, int arg2, int arg3, int arg4, int arg5);
