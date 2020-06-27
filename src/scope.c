#include "include/scope.h"
#include <string.h>

//scope constructor
scope_T *init_scope()
{
	scope_T *scope = calloc(1, sizeof(struct SCOPE_STRUCT));
	scope->function_definitions = (void *)0;
	scope->function_definitions_size = 0;

	return scope;
}

//add a function to the scope
AST_T *scope_add_function_definition(scope_T *scope, AST_T *function_def)
{
	scope->function_definitions_size += 1;

	//check if its empty, if so allcate memory, else re allocate the memory
	if (scope->function_definitions == (void *)0)
	{
		scope->function_definitions = calloc(1, sizeof(struct AST_STRUCT));
	}
	else
	{
		scope->function_definitions = realloc(
			scope->function_definitions,
			scope->function_definitions_size * sizeof(struct AST_STRUCT **));
	}
	//add function to scope
	scope->function_definitions[scope->function_definitions_size - 1] = function_def;

	return function_def;
}

//iterate through the function names to look for the function name
AST_T *scope_get_function_definition(scope_T *scope, const char *function_name)
{
	for (int i = 0; i < scope->function_definitions_size; i++)
	{
		AST_T *fdef = scope->function_definitions[i];
		if (strcmp(fdef->function_definition_name, function_name) == 0)
			return fdef;
	}

	return (void *)0;
}
