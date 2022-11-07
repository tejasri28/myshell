#include "myshell.h"
char* getParentPath(char* newDirPath);
int indexOfLast(char* str, char ch);
int makedir(char* options, char* newDirPath);
int simpleMkdir(char* pathName);


int main(int argc, char** argv){

	char* options = argv[0];
	char** paths = argv+1;
	int numOfPaths = argc-1;
	if(argc==0){
		printf("Enter file name to perform action\n");
		return -1;
	}
	for(int i=0;i<numOfPaths;i++){
		makedir(options,paths[i]);
	}
	return 0;
	
}


int makedir(char* options, char* newDirPath){
	
	char* cwd = getenv("PWD");
	char* fileName = malloc(PATH_MAX);
	
	//resolve relative path at start of pathName
	if(fileName[0]!='/'){
		sprintf(fileName,"%s/%s",cwd,newDirPath);
		//printf("FileName changed to %s\n",fileName);
	}else{
		memcpy(fileName,newDirPath,strlen(newDirPath));
		fileName[strlen(fileName)]=0;
	}

	//get parent path name
	newDirPath = fileName;
	char* parentOfDir = getParentPath(newDirPath);
		
	//check if parent is valid	
	struct stat statBuf;
	if(stat(parentOfDir,&statBuf)<0){
		perror("invalid parent directory");
		return -1;
	}
		
	if(S_ISDIR(statBuf.st_mode)){		
		simpleMkdir(newDirPath);
	}
	return 0;
}

int indexOfLast(char* str, char ch){
	int i=0,index=-1;
	//printf("indexOfLast: %s\n",str);
	for(i = 0; i < strlen(str); i++)
  	{
  		if(str[i] == ch)  
		{
			//printf("%d\t",i);
  			index = i;	
 		}
	}
	return index;
}
int simpleMkdir(char* pathName){
	//printf("simpleMkdir: %s\n",pathName);
	if(mkdir(pathName,0777)<0){
		perror("Unable to create directory");
		return -1;
	}else{
		printf("Directory Created:%s\n",pathName);
		return 0;
	}
	
	
}

char* getParentPath(char* newDirPath){
	char* parent = malloc(PATH_MAX);
	if(newDirPath[strlen(newDirPath)-1]=='/')
		newDirPath[strlen(newDirPath)-1] = 0;
	int length = indexOfLast(newDirPath,'/');
	//printf("indexOf :%d\n",length);
	strncat(parent,newDirPath,length);
	parent[strlen(parent)]=0;
	return parent;	
}

