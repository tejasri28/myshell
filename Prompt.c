#include "myshell.h"


Prompt* createPrompt(){
	Prompt* prompt = malloc(sizeof(Prompt));
	initializePrompt(prompt);
	return prompt;
}

void checkHostName(int hostName){
	if(hostName == -1){
		perror("Issue with retrieving hostname:");
		exit(EXIT_FAILURE);
	} 
}
char* getMyHostName(){
	char* buffer= malloc((sizeof(char))*BUFFERSIZE);

	//retrives host id
	int hostName = gethostname(buffer, sizeof(buffer));
	checkHostName(hostName);	
	
	return buffer;
	
}
char* getCurrentWorkingDirectory(){
	char* s = getenv("PWD");
	if(s==NULL){
		perror("Retreiving present working directory failed:");
		exit(EXIT_FAILURE);
	}
	return s;
}
char* printPrompt(Prompt* prompt){
	char* promptString = malloc(sizeof(char)*BUFFERSIZE);
	sprintf(promptString, "%s@%s:%s$ ",prompt->username,prompt->hostname,prompt->pwd);
	return promptString;
}

void initializePrompt(Prompt* prompt){
	prompt->username = getlogin();
	prompt->hostname = getMyHostName();
	prompt->pwd = getCurrentWorkingDirectory();
}

void setCurrentWorkingDirectory(char* updatedPath){
	prompt->pwd = malloc(PATH_MAX);
	strcpy(prompt->pwd,updatedPath);
	setenv("PWD",prompt->pwd,1);
}

