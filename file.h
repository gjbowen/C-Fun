#ifndef FILE_H
#define FILE_H
struct File 
{ 
   	char fileName[50];
	int rows;
	char** contents;
}; 

typedef struct Tokens{
	char* token;
	char* type;
	struct Tokens *next;
} Token;

void resizeContents(struct File *f);
void setContents(struct File *f);
void setDimensions(struct File *f);
void setFileName(struct File *f,char* fileName);
struct File File(char* fileName);
#endif