#include "myshell.h"

int err_sys(char* errorMessage){
	perror(errorMessage);
	exit(EXIT_FAILURE);
}

//setVariables
//declaring a variable
//if string(with spaces in between),should be enclosed in braces
// a= "Hello World!!"
//if integer or character, will have only 1 token 
// a=1  or a = c
// a=1 2 throw error invalid command : 2
//no spaces after/before =
// 
/*setVariables(){
	char* token = malloc(sizeof(char)*strlen(buf)+1);
	
}*/

int indexOf(char* str,char* substr){
 
    int index = -1;
    for (int i = 0; str[i] != '\0'; i++) {
        index = -1;
        for (int j = 0; substr[j] != '\0'; j++) {
            if (str[i + j] != substr[j]) {
                index = -1;
                break;
            }
            index = i;
        }
        if (index != -1) {
            break;
        }
    }
    return index;
}
int indexOfLast(char* str, char ch){
	int i=0,index=-1;
	for(i = 0; i <= strlen(str); i++)
  	{
  		if(str[i] == ch)  
		{
  			index = i;	
 		}
	}
	return index;
}
/*char* replaceFirstOccurenceOfDoubleDot(char* pathName,char* subString){
	int indexOfSubStr = indexOf(pathName,subString);
	//str[i-k] str[k-len]
	//replace /x/parent/../y with /x/y
	//take substring of path from 0 to indexOfSubStr
	char* kLengthString= malloc(sizeof(char)*(indexOfSubStr));
	memcpy(kLengthString,pathName,indexOfSubStr-1);//skipping copy of /x/parent/ to have only /x/parent
	int indexOfForwardSlash = 
	
}*/
