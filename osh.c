/***********************************************
Unix Shell Final Project
Authors:
Robert Carleton
Christopher Cervantez-Hernandez
Logan Garcia
***********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdbool.h>
#define MAX_LINE 80 /* The maximum length command */

int main(void) {
	char *args[MAX_LINE/2 + 1]; /* command line arguments */
	char *hist[100][MAX_LINE/2 + 1];
	int index = 0;
	int should_run = 1; /* flag to determine when to exit program */
	bool ampersand;
	char *newline;
	char *token;
	int i;
	
	while (should_run) {
		printf("osh>");
		fflush(stdout);		
		ampersand = false;
		char tempArgs[100];
		fgets(tempArgs, sizeof(tempArgs), stdin);
		
		newline = strchr(tempArgs, '\n');
		if (newline) {
  			*newline = 0;
  		}
		
		token = strtok(tempArgs, " "); //holds tokenized result		
		i = 0;
		
		if (strcmp(token, "exit") == 0) {
			should_run = 0;
		}		
		
		else if (strcmp(token, "history") == 0) {
			if (index == 0) {
				printf("No commands in history.\n");
			}
			else {
				for (int v = (index - 1); v >= 0; v--) {
					printf("%i", v + 1);
					for (int x = 0; hist[v][x] != NULL; x++) {
						printf(" %s", hist[v][x]);
					}
					printf("\n");
				}
			}
		}
		
		else {		
			//loop through and tokenize each input
			for ( ; token; i++) {
				if (*token == '&') {
					ampersand = true;
					break;
				}
				else {
					args[i] = token;
					hist[index][i] = args[i];
    				token = strtok(NULL, " ");
    			}
			}
			
			args[i] = NULL;
			hist[histIndex][i] = NULL;			
			index++;					
			pid_t pid = fork();
			
			//check if child process
			if (pid == 0) {
				execvp(args[0], args);
			}
			//check if parent process and ampersand found
			else if (pid > 0 && ampersand == true) {
				wait(NULL);
			}
		}
	}
	return 0;
}
