#define WHITE_TXT     0x07 // Fondo negro, letras blancas
#define LILAC_SQUARE  0x97 // Fondo lila, letras blancas
#define LILAC_TXT     0x09 // Fondo negro, letras lila

void writeToScreen(char key, int fd);
void scrollMainScreen();
void clear();
void clearLine(char * vidmem);
void clearRegisters();
void video_write(char c,int fd);
void video_enter(int fd);
void video_backspace();
void video_tab(int fd);
void insertKey(char key, int * pos, char * vid);
void max_pos(int max);
void reset_upperWritepos();
void reset_writepos();
void k_clear_screen();
void paintLetter(int color);
int getrow(void);
int getcol(void);
