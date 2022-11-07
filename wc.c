#include "myshell.h"

int wc(int fd);

int main(int argc, char**  argv){

	char* options = argv[0];
	char** paths = argv+1;
	int numOfPaths = argc-1;
	if(argc==0){
		printf("Enter file name to perform action\n");
		return -1;
	}
	for(int i=0;i<numOfPaths;i++){
		int fd = open(paths[i],O_RDONLY);
		if(fd<0)
			return -1;
		wc(fd);
	}
	

}

int wc(int fd){

	
	char* buf = malloc(sizeof(char)*BUFFERSIZE2048);
	int bytesRead;
	while (( bytesRead = read(fd, buf, BUFFERSIZE2048)) > 0){
		//printf("Number of bytes read = %d\n",bytesRead);
	}
	//printf("%s\n",buf);	
	int lineCount = 0;
	int wordCount = 0;
	int byteCount = 0;
	
	for(int i=0;i<strlen(buf);i++){
		if(buf[i]=='\n')
			lineCount++;
		byteCount++;
	}
	printf("%d\t",lineCount);
	//calculate lineCount //consequent new lines will be calculated as 1 newline 
	char* token = strtok(buf, "\n");
	
	char* lines[lineCount];
	int i=0;
	while(token!=NULL){
		lines[i] = malloc(sizeof(char)*(strlen(token)+1));
		strcpy(lines[i],token);
		i++;
		token = strtok(NULL,"\n");
	}
	
	lineCount = i;
	for(int i=0;i<lineCount;i++){
		char* token = strtok(lines[i]," \t");
		while(token!=NULL){
			wordCount++;
			token = strtok(NULL," \t");
		}
	}
	
	//TODO Free data 
	printf("%d\t",wordCount);
	printf("%d\n",byteCount);
	
	return 0;

}



