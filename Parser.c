#include "myshell.h"
#include "commands.h"
char* readCommand(){
	char* commandLine = malloc(sizeof(char)*BUFFERSIZE);
	fgets(commandLine,BUFFERSIZE,stdin);
	commandLine[strlen(commandLine)-1]=0;
	return commandLine;
}

char** tokenizeCommand(char* command,int* numberOfTokens){
	//printf("command: %s\n",command);
	char** tokenizedCommand = malloc(sizeof(char)*MAX_TOKENS_IN_COMMAND);
	char* token = strtok(command," ");
	int i=0;
	while(token!=NULL){
		tokenizedCommand[i]= malloc(BUFFERSIZE);
		strcpy(tokenizedCommand[i],token);
		tokenizedCommand[i][strlen(tokenizedCommand[i])]=0;
		token = strtok(NULL," ");
		i++;
	}
	*numberOfTokens = i;
	//for(int i=0;i<*numberOfTokens;i++)
		//printf("%s\n",tokenizedCommand[i]);
	return tokenizedCommand;
}

int validateCommand(char** tokenizedCommand, int numberOfTokens){
	
	for(int i=0;i<AVAIL_COMMANDS_COUNT;i++){
		if(strstr(AVAILABLE_COMMANDS[i],tokenizedCommand[0])){
			return 1;		
		}
	}
	return 0;	
}

char** splitCommandLineByPipe(char* commandline,int* numOfPipes){
	char** pipeSepCmdLine;
	pipeSepCmdLine = malloc(sizeof(char*)*MAX_PIPES);

	char* token= strtok(commandline,"|");
	for (*numOfPipes=0; commandline[*numOfPipes]; commandline[*numOfPipes]=='|' ? *numOfPipes++ : *commandline++);

	if((*numOfPipes)>1){
		return NULL;
	}
	while(token!=NULL){
		char* command = malloc(sizeof(char)*strlen(token));	
		strcpy(command,token);
		pipeSepCmdLine[(*numOfPipes)++]=command;	
		token = strtok(NULL,"|");
	}
	return pipeSepCmdLine;
}

void print_help(){
	printf("Invalid Command\n");
	printf("List of availble commands are :\n");
	for(int i=0;i<AVAIL_COMMANDS_COUNT;i++){
		printf("%d\t%s\n",(i+1),AVAILABLE_COMMANDS[i]);
	}
}
