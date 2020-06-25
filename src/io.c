#include "include/io.h"
#include <stdlib.h>
#include <stdio.h>

//read from a given file name
char *get_file_contents(const char *filepath)
{
	char *buffer = 0;
	long length; //allows us to parse a vary large file

	FILE *f = fopen(filepath, "rb");

	//check if we found a file that can be opened
	if (f)
	{
		fseek(f, 0, SEEK_END);
		length = ftell(f);
		fseek(f, 0, SEEK_SET);

		buffer = calloc(length, length);

		if (buffer)
		{
			fread(buffer, 1, length, f);
		}
		fclose(f);
		return buffer;
	}

	printf("Error reading file %s\n", filepath);
	exit(2);
}
