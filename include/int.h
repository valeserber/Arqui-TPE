extern void writeToMainScreen(const void * buf,size_t count);
extern void scrollMainScreen();
void set_char(char ch);
void int_08();
void int_09(unsigned char scancode);
void int_80h(dword sysCallNumber, dword arg1,dword arg2,
             dword arg3,dword arg4, int arg5);
