/** ls - lists the directory contents
 * 
 * Input variations: 
 * ls 
 * ls filePath
 * ls directoryPath
 * ls directoryPath1/FilePath1 directoryPath2/filePath2 ...
 * options:
 * 1. l - print each entry in separate line
 * 2. a - include hidden files as well -- starting with '.'
 * references: 
 * 1. https://man7.org/linux/man-pages/man3/readdir.3.html
 * 2. https://man7.org/linux/man-pages/man2/readdir.2.html
 * 3. https://man7.org/linux/man-pages/man2/getdents.2.html
 * List of all system calls:
 * https://man7.org/linux/man-pages/man2/syscalls.2.html
*/

#include "myshell.h"

int main(int argc, char** argv){
	/*char* options = NULL;

	if(numberOfTokens == 1){
		char** pathNames = malloc(sizeof(char*)*1);
		int numOfPaths = 1;
		pathNames[0] = getCurrentWorkingDirectory();	
		int rval = ls(options,pathNames,numOfPaths);
		return rval;
	}else if(numberOfTokens>1){						
		options = malloc(sizeof(char)*BUFFERSIZE);
		
		char** pathNames = malloc(sizeof(char*)*numberOfTokens);	
		int nPaths =0;	
		for(int i=1;i<numberOfTokens;i++){
			//printf("%d:%s\n",i,tokenizedCommand[i]);
			if(tokenizedCommand[i][0]=='-'){
				if(strlen(options)==0){
					strcpy(options,tokenizedCommand[i]);
				}
			}
			else{
				pathNames[nPaths++]= tokenizedCommand[i];
			}
		}
		if(nPaths == 0){
			nPaths = 1;				
			pathNames[0] = getCurrentWorkingDirectory();
		}
		ls(options,pathNames,nPaths);
		free(options);
	}*/
	
	char* options = argv[0];
	//printf("options: %s\n",options);
	char** paths = argv+1;
	int numOfPath = argc - 1;
	/*for(int i=0;i<numOfPath;i++){
		printf("%s",paths[i]);
	}*/
	printf("Number of Paths : %d\n",numOfPath);
	if(numOfPath==0){
		paths[0]=".";
		numOfPath =1;
	}
	ls(options,paths,numOfPath);
}

/** ls: list the contents of directory, 
 * if a file, just prints details of the file. 
 * arguments to ls function:
 * @options	: List of options, each options is abbreiviated with single character
 * @pathName: List of pathNames, whose directory contents have to be listed
 * @returns - int: status of ls operations, <0 if unsucessful,>=0 if successful
 */
int ls(char* options, char** pathNames,int numOfPathNames){
	for(int i=0;i<numOfPathNames;i++){
		struct stat statBuf;
		int rval = stat(pathNames[i],&statBuf);

		if(rval<0){
			return -1;
		}
		if(S_ISREG(statBuf.st_mode)||S_ISDIR(statBuf.st_mode)){
			printf("Files at path %s:\n",pathNames[i]);
			printf("--------------------------------------\n");
			if(S_ISREG(statBuf.st_mode)){
				printf("%s",pathNames[i]);
			}else if(S_ISDIR(statBuf.st_mode)){
				DIR* dirp = opendir(pathNames[i]);
				if(dirp==NULL)
					return -1;
				struct dirent* dp;				
				//printf("Options: %s\n",options);
				while((dp = readdir(dirp))!=NULL){
					
					if(options!=NULL){
						if(strstr(options,"a")==NULL && dp->d_name[0]=='.')
							continue;
						printf("%30s\t",dp->d_name);
						
						//get stat of the file in the directory to retrieve meta data of file.
						char* fullPathOfFile = malloc(sizeof(char)*BUFFERSIZE);
						sprintf(fullPathOfFile,"%s/%s",pathNames[i],dp->d_name);
						
						//if(!(dp->d_name[0]=='.')){
							struct stat statBuf1;
							//printf("%s\n",fullPathOfFile);
							int rval = stat(fullPathOfFile,&statBuf1);
							if(rval<0){
								printf("rval = %d\n",rval);
								perror("Stat Error:");
								return -1;
							}
							if(strstr(options,"i"))
								printf("\t%ld",statBuf1.st_ino);
							
							if(strstr(options,"l")){
								char str[32];
								strftime(str, sizeof(str), "%c", localtime(&statBuf1.st_atime));
								printf("\t%10s", str);
								printf("\t%9ld Bytes",statBuf1.st_size);
								printf("\t%9s",getpwuid(statBuf1.st_uid)->pw_name);										
							}
						//}											
						if(strstr(options,"l"))
							printf("\n");
					}else{
						printf("%s\n",dp->d_name);
					}		
				}
				closedir(dirp);												
			}
			printf("\n");
		}
		
	}
	return 0;
}
 
