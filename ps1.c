#include "myshell.h"
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <sys/types.h>
#include "StatusHelper.h"
#define MAX_ATTRIBUTES 57
#define PROC "/proc/"

struct KeyVal{
	char* key;
	char* val;
};
typedef struct KeyVal KeyVal;

int ps2(char*options, char** pids,int npids);
int ps(char* options);

int retrieveProcessPropertiesFromStatusFile(char* pid,KeyVal** processAttributes);
void printProcessAttributes(KeyVal** processAttributes,int getUid);
int getUserId(char* uidString);

int main(int argc, char** argv){
	char* options = argv[0];
	char** paths = argv+1;
	int numOfPids = argc-1;
	if(numOfPids==0)
		ps(options);
	else{
		ps2(options,paths,numOfPids);
	}
	return 0;
}



/**
 * prints all pids in the system with their details status
 */
int ps(char* options){
	struct stat statBuf;
	int rval = stat(PROC,&statBuf);

	if(rval<0){
		perror("Error reading proc");		
		return -1;
	}
	printf("\t%s\t%s\t%s\t\t%s\n","PID","PPID","STATE","COMMAND");
	if(S_ISDIR(statBuf.st_mode)){
		DIR* dirp = opendir(PROC);
		if(dirp==NULL)
			return -1;
		struct dirent* dp;
						
		while((dp = readdir(dirp))!=NULL){				
			if(atoi(dp->d_name)){
				KeyVal* processAttributes[MAX_ATTRIBUTES];				
				int numOfAttrbutes = retrieveProcessPropertiesFromStatusFile(dp->d_name,processAttributes);
				int getUid = (getUserId(processAttributes[UID]->val));	
				//printf("\t%s",processAttributes[UID]->val);
				/*if(getpwuid(getUid)!=NULL)
					printf("\t\t%s\n",getpwuid(getUid)->pw_name);*/
				if(geteuid()==getUid && strlen(options) == 0)
					printProcessAttributes(processAttributes,getUid);
				else if(strlen(options)!=0)
					printProcessAttributes(processAttributes,getUid);
				for(int i=0;i<numOfAttrbutes;i++)
					free(processAttributes[i]);							
			}
		}
	}
}

int retrieveProcessPropertiesFromStatusFile(char* pid, KeyVal** processAttributes){
	char statusPath[BUFFERSIZE512];
	sprintf(statusPath,"%s%s/status",PROC,pid);
	//printf("\n\n%s\n",statusPath);
	
	int fd = open(statusPath,O_RDONLY);
	if(fd<0){
		return -1;
	}
	char* buffer = malloc(sizeof(char)*BUFFERSIZE2048);	
	int bytesRead;
	while (( bytesRead = read(fd, buffer, BUFFERSIZE2048)) > 0){
		//printf("Number of bytes read = %d\n",bytesRead);
	}
	
	char* line = strtok(buffer, "\n");
	int lineCount =0;
	char* lines[MAX_ATTRIBUTES];
	while(line != NULL){		
		lines[lineCount] = malloc(sizeof(char)*BUFFERSIZE512);		
		strcpy(lines[lineCount],line);
		line = strtok(NULL,"\n");
		lineCount++;
	}
	
	close(fd);
	free(buffer);
	int index;
	for(index=0;index<lineCount;index++){
		char* token = malloc(sizeof(char)*BUFFERSIZE512);
		strcpy(token,lines[index]);
		processAttributes[index] = malloc(sizeof(KeyVal));
		processAttributes[index]->key = malloc(sizeof(char)*BUFFERSIZE512);
		processAttributes[index]->key = strtok(token,":");
		processAttributes[index]->val = malloc(sizeof(char)*BUFFERSIZE512);
		processAttributes[index]->val = strtok(NULL,":");
		free(lines[index]);
	}

	return lineCount;
}

void printProcessAttributes(KeyVal** processAttributes,int getUid){

	printf("%s",processAttributes[PID]->val);
	printf("%s",processAttributes[PPID]->val);
	printf("%s",processAttributes[STATE]->val);
	printf("%s",processAttributes[NAME]->val);
	//printf("\t\t%s",getpwuid(getUid)->pw_name);
	printf("\n");
}

/**
 * prints pids of only those mentioned in the system
 */
int ps2(char*options, char** pids,int npids){
	char* header = "PID\t\tPPID\t\tSTATE\t\tCOMMAND\t\tUSERNAME\n";	
	for(int i=0;i<npids;i++){
		KeyVal* processAttributes[MAX_ATTRIBUTES];		
		int numOfAttrbutes = retrieveProcessPropertiesFromStatusFile(pids[i],processAttributes);
		int getUid = (getUserId(processAttributes[UID]->val));	
		//printf("\t%s",processAttributes[UID]->val);
		/*if(getpwuid(getUid)!=NULL)
			printf("\t\t%s\n",getpwuid(getUid)->pw_name);*/
		printProcessAttributes(processAttributes,getUid);
		for(int i=0;i<numOfAttrbutes;i++)
			free(processAttributes[i]);			
	}	
}

int getUserId(char* uidString){
	char* token = strtok(uidString,"\t");
	return atoi(token);
}
