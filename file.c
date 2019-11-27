#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "file.h"

void print_file(File *f){	
	int i;
	for(i=0;i<f->rows;++i)
		printf("%s\n",f->contents[i]);
};

void read_file(File *f){
	set_dimensions(f);

	resize_contents( f);

	set_contents( f);
};

char* get_line(File *f){
	char* str;

	return str;
};

void resize_contents(File *f){
    f->contents = malloc(f->rows * sizeof(char*));
};

void set_contents(File *f){
	FILE *stream = fopen(f->fileName,"r");
	char *line=NULL;
	size_t len,read;
	int i=0;
	while ((read = getline(&line, &len, stream)) != -1)
	{
	    if(strchr(line, '\n'))
	    	--read;
	    /*  Allocate column for each name  */
		f->contents[i] = malloc(read * sizeof(char));
		int j;
		for(j=0;j<read;++j)
			f->contents[i][j] = line[j];
	    
		++i;
	}

	fclose(stream);
	free(stream);
	free(line);
};

void set_dimensions(File *f){
	FILE *stream = fopen(f->fileName,"r");
	char *line=NULL;
	int rows=0;
	size_t len,lineLength;
	
	while ((lineLength = getline(&line, &len, stream)) != -1)
		++rows;

	fclose(stream);
	free(stream);
	free(line);

	f->rows=rows;
};

void set_file_name(File *f,char* fileName){
	strcpy(f->fileName , fileName);
};

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

File file(char* fileName){
	File f;
	
	set_file_name(&f,fileName);

	//add to new read_file function{

	//}
	return f;
};