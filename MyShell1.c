#include "myshell.h"



int main(int argc, char** argv){
	printf("Welcome! You can exit by typing exit/pressing Ctrl-C at any time...\n\n");
	prompt = createPrompt();
	char* buf;
	char* s_prompt = strcat(printPrompt(prompt)," ");
	while((buf = readline(s_prompt))!=NULL){
		if (strlen(buf) > 0) {
			add_history(buf);
    	
			int numberOfTokens = 0;
			if(strstr(buf,"=")){
				//TODO 
				//setVariables
				
			}else if(strstr(buf,"|")){
				//pipe send the output of a command as an input to another file
				//TODO
			}else if(strstr(buf,">")){
				//redirect send the output of a command to a file
				//TODO
				//command 
				//redirect filename
			}else{
				char** tokenizedCommand = tokenizeCommand(buf,&numberOfTokens);
				int isValid = validateCommand(tokenizedCommand,numberOfTokens);
				if(isValid){
					if(strstr(tokenizedCommand[0],"exit")){
						printf("Bye!\n");
						free(buf);
						break;
					}else if(strstr(tokenizedCommand[0],"clear")){
						system("clear");
					}else if(strstr(tokenizedCommand[0],"cd")){
						if(numberOfTokens>2)
							printf("Invalid Command\n");
						else 
							cd(tokenizedCommand[1]);
					}else{
						int rval = executeCommand(tokenizedCommand,numberOfTokens);
						if(rval<0){				
							char* errorMessage=malloc(BUFFERSIZE512);						
							sprintf(errorMessage, "Issue running command %s\n",tokenizedCommand[0]);
							err_sys(errorMessage);
						}
					}
				}else{
					print_help();
				}
				//for(int i=0;i<numberOfTokens;i++)
					//printf("tokenizedCommand[%d] = %s\n",i,tokenizedCommand[i]);
			}
			free(buf);
		}

		free(s_prompt);
		s_prompt = strcat(printPrompt(prompt)," ");		
				//perror("Issue Occured");	
	}
	exit(0);
}

int cd(char* changePath){
	char* fileName=changePath;
	char* cwd = getenv("PWD");
	char* updatedFileName = malloc(PATH_MAX);
	
	if(fileName[0]!='/'){
		sprintf(updatedFileName,"%s/%s",cwd,fileName);
		printf("FileName changed to %s\n",updatedFileName);
	}else{
		memcpy(updatedFileName,fileName,strlen(fileName));
		updatedFileName[strlen(updatedFileName)]=0;
	}
	char* resolvedPathName = malloc(sizeof(char)*PATH_MAX);
	realpath(updatedFileName,resolvedPathName);
	struct stat statBuf;
	
	if(stat(updatedFileName,&statBuf)<0){
		printf("Invalid Directory Path\n");
		return -1;
	}else{
		if(S_ISDIR(statBuf.st_mode)){
			setCurrentWorkingDirectory(resolvedPathName);
		}else{
			printf("Not a directory\n");
			return -1;
		}
	}
	free(resolvedPathName);
	return 0;
}





