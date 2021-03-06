#ifndef SCOPE_H
#define SCOPE_H
#include "AST.h"
typedef struct SCOPE_STRUCT
{
	AST_T **variable_definitions;
	size_t variable_definitions_size;

	AST_T **function_definitions;
	size_t function_definitions_size;
} scope_T;

scope_T *init_scope();

//function methods
AST_T *scope_add_function_definition(scope_T *scope, AST_T *function_def);

AST_T *scope_get_function_definition(scope_T *scope, const char *function_name);

//variable methods
AST_T *scope_add_variable_definition(scope_T *scope, AST_T *variable_def);

AST_T *scope_get_variable_definition(scope_T *scope, const char *function_name);

#endif
