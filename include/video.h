#define WHITE_TXT     0x07 // Black background, white letters
#define LILAC_SQUARE  0x97 // Lilac background, white letters
#define LILAC_TXT     0x09 // Black background, lilac letters

void writeToScreen(char key, int fd);
void scrollMainScreen(void);
void clear(void);
void clearLine(char * vidmem);
void clearRegisters(void);
void video_write(char c,int fd);
void video_enter(int fd);
void video_backspace(void);
void video_tab(int fd);
void insertKey(char key, int * pos, char * vid);
void max_pos(int max);
void reset_upperWritepos(void);
void reset_writepos(void);

/***************************************************************
*k_clear_screen
*
* Borra la pantalla en modo texto color.
****************************************************************/
void k_clear_screen(void);
void paintLetter(int color);
int getrow(void);
int get_row(void);
int getcol(void);
void video_initialize(void);
