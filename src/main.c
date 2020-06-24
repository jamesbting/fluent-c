#include <stdio.h>
#include "include/lexer.h"
#include "include/parser.h"
#include "include/visitor.h"
#include "include/io.h"

void print_help();

int main(int argc, char* argv[])
{
   if(argc < 2) {
	   print_help();
   }
    lexer_T* lexer = init_lexer(
		    get_file_contents(argv[1])
		    );

    parser_T* parser = init_parser(lexer);
    AST_T* root = parser_parse(parser);
    visitor_T* visitor = init_visitor();
    visitor_visit(visitor, root);

    return 0;
}

void print_help() {
	fprintf(stderr,"Fatal: no file was passed as input. Usage: \n  $ fluentc <filename>\n");
	exit(1);
}
