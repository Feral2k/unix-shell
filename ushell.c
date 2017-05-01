/***********************************************
Unix Shell Final Project
Authors:
Robert Carleton
Christopher Cervantez-Hernandez
Logan Garcia
***********************************************/

#include<stdio.h>
#include<unistd.h>
#define MAX_LINE 80

int main() {
	
	char *args[MAX_LINE/2 +1];
	int should_run = 1;
	
	while(should_run) {
		printf("osh> ");
		fflush(stdout);
		
		/**
		* After reading user input, the steps are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command included &, parent will invoke wait()
		*/

	}
	
	return 0;
}