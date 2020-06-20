#ifndef AST_H
#define AST_H
#include <stdlib.h>
typedef struct AST_STRUCT
{
	//types of AST nodes
	enum
	{
		AST_FUNCTION_CALL,
		AST_VARIABLE_DEFINITION,
		AST_VARIABLE,
		AST_STRING,
		AST_COMPOUND
	} type;

	//properties of the AST NODE
	/*AST_VARIABLE_DEFINITION */
	char *variable_definition_variable_name;
	struct AST_STRUCT *variable_definition_value;

	/* AST_VARIABLE*/
	char *variable_name;

	/*AST_FUNCTION_CALL*/
	char *function_call_name;
	struct AST_STRUCT **function_call_arguments; //list of arguments for a function
	size_t function_call_arguments_size;

	/*AST_STRING*/
	char *string_value;

	/*AST_COMPOUND*/
	//a bunch of ast nodes wrapped up into one AST, so its a list of AST nodes
	struct AST_STRUCT **compound_value;
	size_t compound_size;
} AST_T;

AST_T *init_ast(int type);

#endif
