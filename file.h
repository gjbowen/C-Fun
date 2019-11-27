#ifndef FILE_H
#define FILE_H
typedef struct File_t{ 
   	char fileName[50];
	int rows;
	char** contents;
	FILE *stream;
} File; 
char** get_contents(File* f);
void open_file(File* f);
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
File file(char* fileName,char mode);
#endif