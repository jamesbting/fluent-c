#include "include/scope.h"
#include <string.h>

scope_T* init_scope() {
	scope_T* scope =  calloc(1, sizeof(struct SCOPE_STRUCT));
	scope->function_definitions = (void*) 0;
	scope->function_definitions_size = 0;

	return scope;
}

AST_T* scope_add_function_definition(scope_T* scope, AST_T* function_def) {
	scope->function_definitions_size += 1;

	if(scope->function_definitions == (void*) 0) {
		scope->function_definitions = calloc(1, sizeof(struct AST_STRUCT));
	} else {
		scope->function_definitions = realloc(
				scope->function_definitions,
			       	scope->function_definitions_size * sizeof(struct AST_STRUCT**)
				);
	}

	scope->function_definitions[scope->function_definitions_size -1] = function_def;

	return function_def;
	
}


AST_T* scope_get_function_definition(scope_T* scope, const char* function_name) {
	for(int i = 0; i< scope->function_definitions_size; i++) {
		AST_T* fdef = scope->function_definitions[i];
		if(strcmp(fdef->function_definition_name, function_name) == 0) return fdef;
	}

	return (void*) 0;
}
