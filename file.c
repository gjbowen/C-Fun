#include "file.h"

void resize_contents(struct File *f){
    f->contents = malloc(f->rows * sizeof(char*));
};

void set_contents(struct File *f){
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

void set_dimensions(struct File *f){
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

void set_file_name(struct File *f,char* fileName){
	strcpy(f->fileName , fileName);
};



void print_tokens(Token *h) {
	Token *current = h;
	while (current != NULL) {
		printf("%s\n", current->type);
		current = current->next;
	}
}

Token *new_token(char* toke){
	Token *t = malloc(sizeof(Token));
	t->type = malloc(strlen(toke)*sizeof(char));
	strcpy(t->type,toke);
	return t;
}

void push(Token * head, char* val) {
	Token * current = head;
	while(current->next != NULL)
		current = current->next;

	/* now we can add a new variable */
	current->next = new_token(val);
	current->next->next = NULL;
}

Token *set_tokens(struct File *f){
	FILE *stream = fopen(f->fileName,"r");
	Token *head = NULL;
	char *line=NULL;
	size_t len,read;
	int i=0;
	char buff[100]="";

	head = malloc(sizeof(Token));
	head->type = malloc(strlen("START")*sizeof(char));
	strcpy(head->type,"START");
	head->next=NULL;

	while ((read = getline(&line, &len, stream)) != -1)
	{
	    for(i=0;i<read;++i){
	    	if(line[i]=='\r')
	    		continue;
	    	else if(line[i]=='\n'&& strcmp(buff, "")!=0){
				push(head,buff);
				strcpy(buff,"");
		    }	
		    else if(line[i]==' ' && strcmp(buff, "")==0){
	    		continue;
	    	}
	    	else if(line[i]==' '){
				push(head,buff);
				strcpy(buff,"");
			}
			else
				strncat(buff, &line[i], 1); 
	    }
	}
	if(strcmp(buff, "")!=0 ){
		push(head,buff);
	}

	fclose(stream);
	free(stream);
	free(line);

	return head;
};

struct File File(char* fileName){
	struct File f;
	
	set_file_name(&f,fileName);
	Token *t=set_tokens(&f);
	print_tokens(t);
	printlnGreen("hello");

//	set_dimensions(&f);

//	resize_contents(&f);

//	set_contents(&f);
	
	return f;
};