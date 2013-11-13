#define SHELL_SIZE          256
#define PROMPT_LENGTH       4
#define COMMAND_SIZE        14

/*Adds the character to the shell buffer*/
bool addToShellBuffer(char c);

/*Iniatilizes buffer with 0*/
void initialize_shell(void);

void shell_run(void);

bool shBufferIsEmpty(void);

bool shBufferIsFull(void);

void executeCommand(int c);

/* Checks if the arguments is a valid command*/
int checkCommand(char * com);

void searchCommand(void);

/* Lists available commands*/
void help(void);

/* Lists available tests*/
void test();

/* Print letters when a timmer tick interruption arrives*/
void test1();

/* Prints * when a number is multiple of 5. Starts with 0 and adds 1
 * in each iteration
 */
void test2();

/* Tests scanf. Expects integer and prints the result using printf*/
void test3();

/* Tests scanf. Expects string and prints the result using printf*/
void test4();

/* Tests scanf. Expects hexadecimal number and prints the income
 * using printf as a decimal number
 */
void test5();

/* Shifts a number to show carry flag's behaviour*/
void test6();

/* Tests prinft using %x */
void test7();

typedef struct{
  unsigned char buffer[SHELL_SIZE];
  int shell_pos;
}SHELL;

