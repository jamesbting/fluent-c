#include "include/parser.h"
#include <stdio.h>
#include <string.h>

//constructor
parser_T* init_parser(lexer_T* lexer){
	parser_T* parser = calloc(1, sizeof(struct PARSER_STRUCT));
	parser->lexer = lexer;
	parser->current_token = lexer_get_next_token(lexer);

	return parser;
}

void parser_eat(parser_T* parser, int token_type){

	if(parser->current_token->type == token_type) {
		parser->current_token = lexer_get_next_token(parser->lexer);
	} else {
		//unexpected token print an error message and return
		printf("Unexpected token \"%s\" with type %d, expected token with type %d", 
				parser->current_token->value,
			       	parser->current_token->type,
				token_type
			);
		exit(1);
	}
}

AST_T* parser_parse(parser_T* parser){
	return parser_parse_statements(parser);
}

AST_T* parser_parse_statement(parser_T* parser) {
	switch(parser->current_token->type) {
		case TOKEN_ID: return parser_parse_ID(parser);
	
	}
}
AST_T* parser_parse_statements(parser_T* parser){

	//create a compound type node,
	AST_T* compound = init_ast(AST_COMPOUND);

	compound->compound_value = calloc(1, sizeof(struct AST_STRUCT*));

	AST_T* ast_statement = parser_parse_statement(parser);
	compound->compound_value[0] = ast_statement;
	//compound -> compound_size +=1
	
	//while there are semicolons
	while(parser->current_token->type == TOKEN_SEMI) {
		
		parser_eat(parser, TOKEN_SEMI);

		AST_T* ast_statement = parser_parse_statement(parser);
		compound->compound_size += 1; 
		compound->compound_value = realloc(
				compound->compound_value, 
				compound->compound_size * sizeof(struct AST_STRUCT*)
		);

		compound->compound_value[compound->compound_size-1] = ast_statement;
	}

	return compound;
}


AST_T* parser_parse_expression(parser_T* parser);

AST_T* parser_parse_factor(parser_T* parser);

AST_T* parser_parse_term(parser_T* parser);

AST_T* parser_parse_function_call(parser_T* parser);

AST_T* parser_parse_variable(parser_T* parser) {
	parser_eat(parser,TOKEN_ID); //expect var

	char* variable_defintion_variable_name = parser->current_token->value;
	
	parser_eat(parser, TOKEN_ID); //expect variable name
	parser_eat(parser, TOKEN_EQUALS); //epect equals sign for assignment

	AST_T* variable_value = parser_parse_expression(parser);

	AST_T* variable_definition_value = init_ast(AST_VARIABLE_DEFINITION);

	variable_defintion->variable_defintion_variable_name = variable_defintion_variable_name;
	variable_defintion->variable_defintion_value = variable_defintition_value;

	return variable_definition;
}

AST_T* parser_parse_variable(parser_T* parser);

AST_T* parser_parse_string(parser_T* parser);

AST_T* parser_parse_ID(parser_T* parser) {
	if(strcmp(parser->current_token->value, "var") == 0) {
		return parser_parser_variable_definition(parser);
	} else {
		return parser_parser_variable(parser);
	}
}
