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
	char *line=NULL;
	size_t len,read;
	if((read = getline(&line, &len, f->stream)) == -1 ){
		fclose(f->stream);
		free(f->stream);
		return NULL;
	}
	return line;
};

void resize_contents(File *f){
    f->contents = malloc(f->rows * sizeof(char*));
};

char** get_contents(File* f){
	return f->contents;
};

void set_contents(File *f){
	f->stream = fopen(f->fileName,"r");
	char *line=NULL;
	size_t len,read;
	int i=0;
	while ((read = getline(&line, &len, f->stream)) != -1)
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

	fclose(f->stream);
	free(f->stream);
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

void open_file(File* f,char* mode){
	f->stream = fopen(f->fileName,mode);
}
void close_file(File* f){
	fclose(f->stream);
}

void write_line(File* f,char* line){
	fputs (line,f->stream);
	fputs ("\r\n",f->stream);
}

File file(char* fileName,char* mode){
	File f;
	set_file_name(&f,fileName);
	if(strcmp(mode,"r")==0||strcmp(mode,"R")==0)
		open_file(&f,mode);
	else if(strcmp(mode,"w")==0||strcmp(mode,"W")==0)
		open_file(&f,mode);
	else if(strcmp(mode,"a")==0||strcmp(mode,"A")==0)
		open_file(&f,mode);

	return f;
};
