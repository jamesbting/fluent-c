#include "include/lexer.h"
#include "include/token.h"
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//constructor method for a lexer
lexer_T *init_lexer(char *contents)
{
	lexer_T *lexer = calloc(1, sizeof(struct LEXER_STRUCT));
	lexer->contents = contents;
	lexer->i = 0;
	lexer->c = contents[lexer->i];
	return lexer;
}

//method that moves the lexer to the next character in the source code, if possible
void lexer_advance(lexer_T *lexer)
{
	//check if there is a next character to advance to
	if (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		lexer->i += 1;
		lexer->c = lexer->contents[lexer->i];
	}
}

//method that skips the white space in the source code
void lexer_skip_whitespace(lexer_T *lexer)
{
	while (lexer->c == ' ' || lexer->c == 10)
	{ //skip spaces and new lines (10 is new lines)
		lexer_advance(lexer);
	}
}

//method that returns a struct representing the next token in the source code
token_T *lexer_get_next_token(lexer_T *lexer)
{
	while (lexer->c != '\0' && lexer->i < strlen(lexer->contents))
	{
		//if we find the white space, skip until we find the next non whitespace character
		if (lexer->c == ' ' || lexer->c == 10)
			lexer_skip_whitespace(lexer);

		if (lexer->c == '"')
			return lexer_collect_string(lexer);

		if (isalnum(lexer->c))
			return lexer_collect_id(lexer);
		//if we dont have a white space, then do something based on the character
		//be careful of the switch antipattern
		switch (lexer->c)
		{
		case '=':
			return lexer_advance_with_token(lexer, init_token(TOKEN_EQUALS, lexer_get_current_char_as_string(lexer)));
			break;
		case ';':
			return lexer_advance_with_token(lexer, init_token(TOKEN_SEMI, lexer_get_current_char_as_string(lexer)));
			break;
		case '(':
			return lexer_advance_with_token(lexer, init_token(TOKEN_LPAREN, lexer_get_current_char_as_string(lexer)));
			break;
		case ')':
			return lexer_advance_with_token(lexer, init_token(TOKEN_RPAREN, lexer_get_current_char_as_string(lexer)));
			break;
		case ',':
			return lexer_advance_with_token(lexer, init_token(TOKEN_COMMA, lexer_get_current_char_as_string(lexer)));
			break;
		}
	}
	// if we reached here, we have reached the end so make a EOF token, and return it
	return init_token(TOKEN_EOF, '\0');
}

//define how to parse IDs
token_T *lexer_collect_id(lexer_T *lexer)
{

	char *value = calloc(1, sizeof(char));
	value[0] = '\0';

	//add characters while the name is alpha numeric
	while (isalnum(lexer->c))
	{
		char *s = lexer_get_current_char_as_string(lexer);
		value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
		strcat(value, s);
		lexer_advance(lexer);
	}
	return init_token(TOKEN_ID, value);
}

//define how to parse a string
token_T *lexer_collect_string(lexer_T *lexer)
{
	lexer_advance(lexer); //skip opening quote
	char *value = calloc(1, sizeof(char));
	value[0] = '\0';

	while (lexer->c != '"')
	{
		char *s = lexer_get_current_char_as_string(lexer);
		//reallocate memory value to fit the new string
		value = realloc(value, (strlen(value) + strlen(s) + 1) * sizeof(char));
		strcat(value, s);
		lexer_advance(lexer);
	}
	lexer_advance(lexer); //skip end quote

	return init_token(TOKEN_STRING, value);
}

//helper function
token_T *lexer_advance_with_token(lexer_T *lexer, token_T *token)
{
	lexer_advance(lexer);

	return token;
}

//return a string representing the character at the current lexer position
char *lexer_get_current_char_as_string(lexer_T *lexer)
{
	char *str = calloc(2, sizeof(char));
	str[0] = lexer->c;
	str[1] = '\0';

	return str;
}
