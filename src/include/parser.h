#ifndef PARSER_H
#define PARSER_H
#include "AST.h"
#include "lexer.h"
#include "scope.h"

typedef struct PARSER_STRUCT {
	lexer_T* lexer;
	token_T* current_token;
	token_T* prev_token;
	scope_T* scope; //global scope
}parser_T;

parser_T* init_parser(lexer_T* lexer);

//expect method a certain token, and if we get an unexpected token, then terminate the program
void parser_eat(parser_T* parser, int token_type, scope_T* scope);

//function that will give the whole ast tree of the entire source code
AST_T* parser_parse(parser_T* parser, scope_T* scope);

AST_T* parser_parse_statement(parser_T* parser, scope_T* scope);

AST_T* parser_parse_statements(parser_T* parser, scope_T* scope);

AST_T* parser_parse_expression(parser_T* parser, scope_T* scope);

AST_T* parser_parse_factor(parser_T* parser, scope_T* scope);

AST_T* parser_parse_term(parser_T* parser, scope_T* scope);

AST_T* parser_parse_function_call(parser_T* parser, scope_T* scope);

AST_T* parser_parser_function_defintion(parser_T* parser, scope_T* scope);

AST_T* parser_parse_variable(parser_T* parser, scope_T* scope);

AST_T* parser_parse_variable_defintion(parser_T* parser, scope_T* scope);

AST_T* parser_parse_string(parser_T* parser, scope_T* scope);

AST_T* parser_parse_ID(parser_T* parser, scope_T* scope);

#endif
