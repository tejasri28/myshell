#include "myshell.h"

/*cat command 
 * options & Variations
 * simple cat: given a file print the file contents
 * simple options: cat -n : print line number at the start of each line being printed
 * 				   cat -E : show ends of each line with $
 * cat - concatenate files and print on the standard output
 * print the contents of each line list one after the other
*/


int cat(char* options,char* filepath){
	struct stat statBuf;
	if(stat(filepath,&statBuf)<0){
		perror("Unable to check file metadata");
		return -1;
	}
	
	if(S_ISREG(statBuf.st_mode)){
		int fd = open(filepath,O_RDONLY);
		if(fd<0){
			perror("Unable to open file");
			return -1;			
		}
		char* buf = malloc(sizeof(char)*statBuf.st_size);
		int bytesRead;
		while (( bytesRead = read(fd, buf, statBuf.st_size)) > 0){
			//printf("Number of bytes read = %d\n",bytesRead);
		}
		char* line = strtok(buf, "\n");
		int lineCount =0;
		while(line != NULL){
			if(strstr(options,"n"))
			printf("%d:\t",lineCount+1);		
			printf("%s",line);
			line = strtok(NULL,"\n");
			if(strstr(options,"E"))
			printf("$");
			printf("\n");			
			lineCount++;
		}
	}
	return 0;
}
int catFiles(char* options,char** pathNames,int numOfPaths){
	for(int i=0;i<numOfPaths;i++){
		if(cat(options,pathNames[i])<0)
			return -1;
	}
}
int main(int argc, char** argv){
	//cat("-nE",argv[1]);
	char* options = argv[0];
	char** paths = argv+1;
	int numOfPaths = argc-1;
	if(numOfPaths==0)
		printf("No Files passed to cat\n");
	else{
		catFiles(options,paths,numOfPaths);
	}
	return 0;
}
