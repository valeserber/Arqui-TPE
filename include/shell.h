#define SHELL_SIZE          256
#define PROMPT_LENGTH       4
#define COMMAND_SIZE        14

bool addToShellBuffer(char c);

void initialize_shell(void);

void shell_run(void);

bool shBufferIsEmpty(void);

bool shBufferIsFull(void);

void executeCommand(int c);

int checkCommand(char * com);

void searchCommand(void);

void help(void);

void test();

void test1();

void test2();

void test3();

void test4();

void test5();

void test6();

void test7();

typedef struct{
  unsigned char buffer[SHELL_SIZE];
  int shell_pos;
}SHELL;

