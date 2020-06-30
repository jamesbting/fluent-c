#include "include/visitor.h"
#include <stdio.h>
#include <string.h>
#include "include/scope.h"
//built in print function that will print the value of the print parameters to STDOUT
//only supports strings at the moment
static AST_T *builtin_function_print(visitor_T *visitor, AST_T **args, int args_size)
{
    for (int i = 0; i < args_size; i++)
    {
        AST_T *visited_ast = visitor_visit(visitor, args[i]);

        switch (visited_ast->type)
        {
        case AST_STRING:
            printf("%s\n", visited_ast->string_value);
            break;
        default:
            printf("%p\n", visited_ast);
            break; //not a printable value, print the reference to the value instead
        }
    }

    return init_ast(AST_NOOP);
}

//constructor
visitor_T *init_visitor()
{
    visitor_T *visitor = calloc(1, sizeof(struct VISITOR_STRUCT));

    return visitor;
}

//main entry point
//visit a specified node, and depending on the node type, perform different actions
AST_T *visitor_visit(visitor_T *visitor, AST_T *node)
{

    //switch on the type of node
    switch (node->type)
    {
    case AST_VARIABLE_DEFINITION:
        return visitor_visit_variable_definition(visitor, node);
        break;
    case AST_VARIABLE:
        return visitor_visit_variable(visitor, node);
        break;
    case AST_FUNCTION_DEFINITION:
        return visitor_visit_function_definition(visitor, node);
        break;
    case AST_FUNCTION_CALL:
        return visitor_visit_function_call(visitor, node);
        break;
    case AST_STRING:
        return visitor_visit_string(visitor, node);
        break;
    case AST_COMPOUND:
        return visitor_visit_compound(visitor, node);
        break;
    case AST_NOOP:
        return node;
        break;
    }

    //unexpected node type, fatal so terminate the program
    printf("Uncaught statement of type `%d`\n", node->type);
    exit(1);

    // technically unreachable code, but its here for prettyness purposes
    return init_ast(AST_NOOP);
}

//user is trying to declare a variable
AST_T *visitor_visit_variable_definition(visitor_T *visitor, AST_T *node)
{

    scope_add_variable_definition(node->scope, node);
    return node;
}

//user is trying to access a previously declared variable
AST_T *visitor_visit_variable(visitor_T *visitor, AST_T *node)
{
    AST_T *vdef = scope_get_variable_definition(
        node->scope,
        node->variable_name);
    //if we found a variable defintion, visit it and get the value
    if (vdef != (void *)0)
        return visitor_visit(visitor, vdef->variable_definition_value);

    //variable name does not exist
    printf("Undefined variable '%s`\n", node->variable_name);
    exit(1);
}

//visit a function defintion node
AST_T *visitor_visit_function_definition(visitor_T *visitor, AST_T *node)
{
    scope_add_function_definition(node->scope, node);
    return node;
}

//visit variable
AST_T *visitor_visit_function_call(visitor_T *visitor, AST_T *node)
{
    if (strcmp(node->function_call_name, "print") == 0)
    {
        return builtin_function_print(visitor, node->function_call_arguments, node->function_call_arguments_size);
    }

    //not a built in function, check for defined function
    AST_T *fdef = scope_get_function_definition(
        node->scope,
        node->function_call_name);

    //check if the specified function has be defined
    if (fdef == (void *)0)
    {
	printf("Undefined method '%s'\n", node->function_call_name);
	exit(1);
    }
   
    //append arguments as variables to the function's scope  
   for(int i = 0; i < node->function_call_arguments_size; i++) 
   {
	   //get variable from function definition arguments
	AST_T* ast_var = (AST_T*) fdef->function_definition_args[i];
	//get value from function call arguments
	AST_T* ast_value = (AST_T*)  node->function_call_arguments[i];
	
	AST_T* ast_vardef = init_ast(AST_VARIABLE_DEFINITION);
	//AST_T* variable_def = init_ast(AST_VARIABLE_DEFINITION);
	
	//copy the variable value
	ast_vardef->variable_definition_value = ast_value;
	//copy the variable name
	ast_vardef->variable_definition_variable_name = (char*) calloc(strlen(ast_var->variable_name)+1, sizeof(char));
	strcpy(ast_vardef->variable_definition_variable_name, ast_var->variable_name);
	//push to scope
	scope_add_variable_definition(
			fdef->function_definition_body->scope,
			ast_vardef
	);

   } 
	

    return visitor_visit(visitor, fdef->function_definition_body);
  
}

AST_T *visitor_visit_string(visitor_T *visitor, AST_T *node)
{
    return node;
}

//iteratively visit each statement in a compound node
AST_T *visitor_visit_compound(visitor_T *visitor, AST_T *node)
{
    for (int i = 0; i < node->compound_size; i++)
    {
        visitor_visit(visitor, node->compound_value[i]);
    }

    return init_ast(AST_NOOP);
}
