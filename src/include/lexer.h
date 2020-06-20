#ifndef LEXER_H
#define LEXER_H
#include "token.h"


typedef struct LEXER_STRUCT {
	char c;
	unsigned int i; //curent index
	char* contents; //source code
}lexer_T;

//constructor method
lexer_T* init_lexer(char* contents);

//method that moves the lexer to the next character in the source code, if possible
void lexer_advance(lexer_T* lexer);

//method that skips the white space in the source code
void lexer_skip_whitespace(lexer_T* lexer);

//method that returns a struct representing the next token in the source code
token_T* lexer_get_next_token(lexer_T* lexer);

//define how to parse a string
token_T* lexer_collect_string(lexer_T* lexer);

//function to collect the keywords
token_T* lexer_collect_id(lexer_T* lexer);

//helper function
token_T* lexer_advance_with_token(lexer_T* lexer, token_T* token);

//return a string representing the character at the current lexer position
char* lexer_get_current_char_as_string(lexer_T* lexer);
#endif
