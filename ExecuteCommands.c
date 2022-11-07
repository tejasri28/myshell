#include "myshell.h"


int executeCommand(char** tokenizedCommand,int numberOfTokens){
	//for token 0 == command
	//separate options from tokenized command, will be passed as argv[1]
	//other arguments to command will be passed as argv[2],..
	//argv[0] == "./bin/"tokenizedCommand[0]+".out"
	

	char* options = getOptions(tokenizedCommand,numberOfTokens);
		
	int index = 0;
	char* args[numberOfTokens];
	args[index]=options;index++;

	for(int i=1;i<numberOfTokens;i++){
		if(tokenizedCommand[i][0]!='-'){
			args[index]=tokenizedCommand[i];		
			index++;
		}
	}
	args[index]=NULL;
	/*for(int j=0;j<index;j++)
		printf("%s\n",args[j]);*/
		
	
	if(strstr(tokenizedCommand[0],"pwd")){
		printf("%s\n",getCurrentWorkingDirectory());
	}
	int status =0;
	int childpid=fork(),wpid;
	if(childpid==0){
		char* executablePath = malloc(PATH_MAX);
		sprintf(executablePath,"./bin/%s.out",tokenizedCommand[0]);
		//printf("%s\n",executablePath);
		if(execv(executablePath,args)<0){
			perror("Cannot do execv\n");
		}
	}else{
		while ((wpid = wait(&status)) > 0);
	}
	return 0;
}

char* getOptions(char** tokenizedCommand,int numOfTokens){


	char* options = (char*)malloc(sizeof(char)*(int)BUFFERSIZE);
	//printf("options:%s\n",options);
	for(int i=1;i<numOfTokens;i++){
		if(tokenizedCommand[i][0]=='-'){
			//printf("tokenizedCommand[%d]+1:%s\n",i,tokenizedCommand[i]+1);
			strcat(options,tokenizedCommand[i]+1);
		}
	}
	options[strlen(options)]=0;

	return options;
}	
/*
int main(int argc, char** argv){
	executeCommand(argv,argc);
}*/

