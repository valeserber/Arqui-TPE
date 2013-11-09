#define SHELL_SIZE          256
#define PROMPT_LENGTH       4
#define COMMAND_SIZE        6

bool addToShellBuffer(char c);

void initialize_shell();

void shell_run();

bool shBufferIsEmpty();

bool shBufferIsFull();

void executeCommand(int c);

int checkCommand(char * com);

void searchCommand();

typedef struct{
  unsigned char buffer[SHELL_SIZE];
  int shell_pos;
}SHELL;

