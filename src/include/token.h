#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT
{
	//type of the token
	//Fluent-C currently has support for strings and functions
	enum
	{
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_STRING,
		TOKEN_SEMI,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_RBRACE,
		TOKEN_LBRACE,
		TOKEN_COMMA,
		TOKEN_EOF
	} type;
	char *value;
} token_T;

//constructor for the token
token_T *init_token(int type, char *value);
#endif
