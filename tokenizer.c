#include "tokenizer.h"
/*
	USAGE: 	
		Token* t = tokenizer(file_name);
		print_tokens(t);
*/
Token *tokenizer(char* fileName){
	Token *t=set_tokens(fileName);
	return t;
}

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

void push(Token * head, char* val){
	Token * current = head;
	while(current->next != NULL)
		current = current->next;

	/* now we can add a new variable */
	current->next = new_token(val);
	current->next->next = NULL;
}

Token *set_tokens(char* fileName){
	FILE *stream = fopen(fileName,"r");
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