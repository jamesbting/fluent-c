#include "include/parser.h"
#include <stdio.h>
#include <string.h>

//parser struct class

parser_T *init_parser(lexer_T *lexer)
{
    parser_T *parser = calloc(1, sizeof(struct PARSER_STRUCT));
    parser->lexer = lexer;
    parser->current_token = lexer_get_next_token(lexer);
    parser->prev_token = parser->current_token;

    return parser;
}

//go to the next token, and check if that token is an expected token, if raise an error message and terminate the program
void parser_eat(parser_T *parser, int token_type)
{
    if (parser->current_token->type == token_type)
    {
        parser->prev_token = parser->current_token;
        parser->current_token = lexer_get_next_token(parser->lexer);
    }
    else
    {
        printf(
            "Unexpected token `%s`, with type %d",
            parser->current_token->value,
            parser->current_token->type);
        exit(1);
    }
}

//main entry point for the parser
AST_T *parser_parse(parser_T *parser)
{
    return parser_parse_statements(parser);
}

//parse a single statement
AST_T *parser_parse_statement(parser_T *parser)
{
    switch (parser->current_token->type)
    {
    case TOKEN_ID:
        return parser_parse_ID(parser);
    }

    return init_ast(AST_NOOP);
}

//parser multiple statements
AST_T *parser_parse_statements(parser_T *parser)
{

    //make a compound statement node, and add all the statement into that node
    AST_T *compound = init_ast(AST_COMPOUND);
    compound->compound_value = calloc(1, sizeof(struct AST_STRUCT *));

    //add first statement to compound statement node
    AST_T *ast_statement = parser_parse_statement(parser);
    compound->compound_value[0] = ast_statement;
    compound->compound_size += 1;

    //while there are semi colons at the end of the statement
    while (parser->current_token->type == TOKEN_SEMI)
    {
        parser_eat(parser, TOKEN_SEMI);

        AST_T *ast_statement = parser_parse_statement(parser);

        //if its not null, add it to the compound statement node
        if (ast_statement)
        {
            compound->compound_size += 1;
            compound->compound_value = realloc(
                compound->compound_value,
                compound->compound_size * sizeof(struct AST_STRUCT *));
            compound->compound_value[compound->compound_size - 1] = ast_statement;
        }
    }

    return compound;
}

//parse an expression, if its a string or id
AST_T *parser_parse_expr(parser_T *parser)
{
    switch (parser->current_token->type)
    {
    case TOKEN_STRING:
        return parser_parse_string(parser);
    case TOKEN_ID:
        return parser_parse_ID(parser);
    }

    return init_ast(AST_NOOP);
}

AST_T *parser_parse_factor(parser_T *parser)
{
}

AST_T *parser_parse_term(parser_T *parser)
{
}

//parse a function call, and add all the arguments to the function call node
AST_T *parser_parse_function_call(parser_T *parser)
{
    AST_T *function_call = init_ast(AST_FUNCTION_CALL);

    function_call->function_call_name = parser->prev_token->value;
    parser_eat(parser, TOKEN_LPAREN);

    function_call->function_call_arguments = calloc(1, sizeof(struct AST_STRUCT *));

    AST_T *ast_expr = parser_parse_expr(parser);
    function_call->function_call_arguments[0] = ast_expr;
    function_call->function_call_arguments_size += 1;

    //use a comma to separate the function calls
    while (parser->current_token->type == TOKEN_COMMA)
    {
        parser_eat(parser, TOKEN_COMMA);

        AST_T *ast_expr = parser_parse_expr(parser);
        function_call->function_call_arguments_size += 1;
        function_call->function_call_arguments = realloc(
            function_call->function_call_arguments,
            function_call->function_call_arguments_size * sizeof(struct AST_STRUCT *));
        function_call->function_call_arguments[function_call->function_call_arguments_size - 1] = ast_expr;
    }
    parser_eat(parser, TOKEN_RPAREN);

    return function_call;
}

//parse a variable defintion, and store the value
AST_T *parser_parse_variable_definition(parser_T *parser)
{
    parser_eat(parser, TOKEN_ID); // expect "var" keyword
    char *variable_definition_variable_name = parser->current_token->value;
    parser_eat(parser, TOKEN_ID);     // expect the variable name
    parser_eat(parser, TOKEN_EQUALS); //expect the assignment operator "="
    AST_T *variable_definition_value = parser_parse_expr(parser);

    AST_T *variable_definition = init_ast(AST_VARIABLE_DEFINITION);
    variable_definition->variable_definition_variable_name = variable_definition_variable_name;
    variable_definition->variable_definition_value = variable_definition_value;

    return variable_definition;
}

//parse accessing a variable and add it to the AST
AST_T *parser_parse_variable(parser_T *parser)
{

    char *token_value = parser->current_token->value;
    parser_eat(parser, TOKEN_ID); // var name or function call name

    //we found a left parentheses, so assume the user is access a variable, but is instead trying to call a
    //a function
    if (parser->current_token->type == TOKEN_LPAREN)
        return parser_parse_function_call(parser);

    AST_T *ast_variable = init_ast(AST_VARIABLE);
    ast_variable->variable_name = token_value;

    return ast_variable;
}

//parse a string into the AST
AST_T *parser_parse_string(parser_T *parser)
{
    AST_T *ast_string = init_ast(AST_STRING);
    ast_string->string_value = parser->current_token->value;

    parser_eat(parser, TOKEN_STRING);

    return ast_string;
}

//assume if we have an id, and the current value is var that the user is trying to assign a new variable, if not,
//then assume they are trying to access the name of a new variable
AST_T *parser_parse_ID(parser_T *parser)
{
    if (strcmp(parser->current_token->value, "var") == 0)
    {
        return parser_parse_variable_definition(parser);
    }
    else
    {
        return parser_parse_variable(parser);
    }
}
