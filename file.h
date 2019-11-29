#ifndef FILE_H
#define FILE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef struct File_t{ 
   	char fileName[50];
	int rows;
	char** contents;
	FILE *stream;
} File; 
void write_line(File* f,char* line);
void close_file(File* f);
char** get_contents(File* f);
void open_file(File* f,char* mode);
void resize_contents(File *f);
void read_file(File *f);
char* get_line(File *f);
void print_file(File *f);
int columns_in_csv(char* str);
char** csv_to_array(char* str,int size);
void resize_contents(File *f);
void set_contents(File *f);
void set_dimensions(File *f);
void set_file_name(File *f,char* fileName);
File file(char* fileName,char* mode);
#endif