#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "color.c"
#include "file.c"

int columns_in_csv(char* str){
	int i,tokens=0;
	bool inParen = false;
	for(i=0;i<strlen(str);++i){
		if(!inParen && str[i]=='\"'){ //START OF STRING.
			inParen = true;
			continue;
		}
		else if(inParen && str[i]=='\"'){ //END OF STRING!
			inParen = false;
			continue;
		}
		else if(inParen) //still a part of a string..
			continue;
		else if(str[i]==',') //another comma
			++tokens;
	}
	return tokens+1;
}

char** csv_to_array(char* str,int size){
	int i,tokens=0;
	bool inParen = false;
	char buff[100]="";
	//initialize size of array
	char** contents = malloc(size * sizeof(char));

	for(i=0;i<strlen(str);++i){
		if(!inParen && str[i]=='\"'){ //START OF STRING.
			inParen = true;
			continue;
		}
		else if(inParen && str[i]=='\"'){ //END OF STRING!
			inParen = false;
			continue;
		}
		else if(inParen){ //still a part of a string..
			strncat(buff, &str[i], 1); 
			continue;
		}
		else if(str[i]==','){ //another comma
			//reallocate size of string to buffer size
			contents[tokens] = malloc(strlen(buff) * sizeof(char));
			
			//copy the buffer into the array
			strcpy(contents[tokens],buff);
			
			//reinitialize the buffer
			strcpy(buff,"");
			++tokens;
		}
		else //keep adding to buffer
			strncat(buff, &str[i], 1); 
	}
	//reallocate size of string to buffer size
	contents[tokens] = malloc(strlen(buff) * sizeof(char));
	
	//flush whats left into last slot
	strcpy(contents[tokens],buff);

	return contents;
}


int main(void)
{

	struct File f = File("program.txt");
	
	return 0;
}
