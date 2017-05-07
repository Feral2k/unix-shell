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
	int should_run = 1; /* flag to determine when to exit program */
	
	while (should_run) {
		printf("osh>");
		fflush(stdout);
		bool ampersand = false;
		char tempArgs[100];
		fgets(tempArgs, sizeof(tempArgs), stdin);
		
		char *newline = strchr(tempArgs, '\n');
		if (newline) {
  			*newline = 0;
  		}
		
		char* token = strtok(tempArgs, " "); //holds tokenized result		
		int i = 0;
		
		if (strcmp(token, "exit") == 0) {
			should_run = 0;
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
					printf("token: %s\n", args[i]);
    				token = strtok(NULL, " ");
    			}
			}
			
			args[i] = NULL;					
			pid_t pid = fork();
			
			//check if child process
			if (pid == 0) {
				execvp(args[0], args);
				printf("\n");
			}
			//check if parent process and ampersand found
			else if (pid > 0 && ampersand == true) {
				wait(NULL);
			}
		}
			
			//should_run = 0;
	
		/**
		* After reading user input, the steps are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command included &, parent will invoke wait()
		*/
	}
	return 0;
}
