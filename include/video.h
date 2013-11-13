#define WHITE_TXT     0x07 // Black background, white letters
#define LILAC_SQUARE  0x97 // Lilac background, white letters
#define LILAC_TXT     0x09 // Black background, lilac letters


/*Decides how to write according to the fd*/
void writeToScreen(char key, int fd);

void scrollMainScreen(void);

/*Clears main screen*/
void clear(void);

/*Clears one row*/
void clearLine(char * vidmem);

/*Clears upper screen*/
void clearRegisters(void);

/*Decides how to write according to the character*/
void video_write(char c,int fd);

void video_enter(int fd);

void video_backspace(void);

void video_tab(int fd);

/*Writes the character on screen*/
void insertKey(char key, int * pos, char * vid);

/*Sets a limit of ammount of characters than can be erased*/
void max_pos(int max);

void reset_upperWritepos(void);

void reset_writepos(void);

/*Clears all the screen*/
void k_clear_screen(void);

void paintLetter(int color);

int getrow(void);

int get_row(void);

int getcol(void);

void video_initialize(void);
