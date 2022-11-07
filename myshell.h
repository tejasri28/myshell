#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
#include <sys/types.h>
#include<string.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include <pwd.h> //to support uid to username mapping. Can also be done using /etc/passwd file parsing

#define BUFFERSIZE 256
#define BUFFERSIZE512 512
#define BUFFERSIZE1024 1024
#define BUFFERSIZE2048 2048
#define MAX_PIPES 2
#define MAX_ARGUMENTS 6
#include <readline/readline.h>
#include <readline/history.h>

struct Prompt{
	char* hostname;
	char* username;
	char* pwd;
};

typedef struct Prompt Prompt;

Prompt* prompt;

Prompt* createPrompt();
void checkHostName(int hostName);
char* getMyHostName();
char* getCurrentWorkingDirectory();
char* printPrompt(Prompt* prompt);
void initializePrompt(Prompt* prompt);
void setCurrentWorkingDirectory(char* updatedPath);
//error messages
int err_sys(char* errorMessage);	
void print_help();

//MyShell1.c
int cd(char* changePath);

//Parser.c 
#define MAX_TOKENS_IN_COMMAND 10
char* readCommand();
char** tokenizeCommand(char* command,int* numberOfTokens);
int validateCommand(char** tokenizedCommand, int numberOfTokens);
char** splitCommandLineByPipe(char* commandline,int* numOfPipes);

//ExecuteCommands.c
int executeCommand(char** tokenizedCommand,int numberOfTokens);
int executePipedCommand(char** pipeSepCmdLine);
char* getOptions(char** tokenizedCommand,int numOfTokens);
//ls.c

int ls(char* options, char** pathNames,int numOfPathNames);


