#ifndef TOKENIZER_H
#define TOKENIZER_H
typedef struct Tokens{
	char* token;
	char* type;
	struct Tokens *next;
} Token;

void print_tokens(Token *h);
Token *new_token(char* toke);
void push(Token * head, char* val);
Token *set_tokens(char* fileName);
Token *tokenizer(char* fileName);
#endif