#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#define MAX_LINE 80

int main()
{

	char **args; 
		args = (char**) malloc(MAX_LINE/2 + 1); //variable to take the argument
		int i = 0;
		for(i = 0; i < MAX_LINE/2 + 1; i++)
		{
			args[i] = (char*) malloc(MAX_LINE/2 + 1);
			args[i] = "test";
		}
	char ***history;
	history = malloc(MAX_LINE/2 + 1); //variable to hold the history
	history[0] = args;
	printf("%s" ,history[0][0]);
}