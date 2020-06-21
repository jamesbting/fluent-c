#ifndef TOKEN_H
#define TOKEN_H
typedef struct TOKEN_STRUCT {
	//type of the token
	enum {
		TOKEN_ID,
		TOKEN_EQUALS,
		TOKEN_STRING,
		TOKEN_SEMI,
		TOKEN_LPAREN,
		TOKEN_RPAREN,
		TOKEN_COMMA,
		TOKEN_EOF
	}type;
	char* value;
}token_T;

//constructor for the token
token_T* init_token(int type, char* value);
#endif
