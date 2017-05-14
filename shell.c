#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>
#define MAX_LINE 80
int main()
{
	char ***history;
	history = malloc(MAX_LINE/2 + 1); //variable to hold the history
	 //end memeory allocation
	
	//variables
	char* input = (char*) malloc(MAX_LINE);
	int should_run = 1;
	int lastWhiteSpace = 0;
	int currentIndex = 0;
	int count = 0;
	int historyCount = 0;
	int parallelFlag = 0;
	int previousCommandFlag = 0;
	//end variables

	while(should_run) //start shell loop
	{
		printf("osh>"); //print terminal prompt
		fgets(input, MAX_LINE, stdin); //get input from the user
		char **args; 
		args = (char**) malloc(MAX_LINE/2 + 1); //variable to take the argument
		int i, j = 0;
		char* exitCondition = (char*) malloc(MAX_LINE/2 + 1);
		i = lastWhiteSpace = 0;
		//parse the input
		if(strncmp(input, "exit", 4))
		{
			while(input[i])
			{
				if(input[i] == ' ' || input[i] == '\n') //checking for breaks for arguments
				{
					printf("allocating\n");
					args[j] = malloc(MAX_LINE/2 + 1);
					while(lastWhiteSpace < i) //put all characters between the lastWhiteSpace and i into args
					{
						if(input[lastWhiteSpace] == ' ')
						{
							printf("%i ", i);
							lastWhiteSpace++;
							currentIndex = 0;
						}
						else if(input[lastWhiteSpace] == '\n')
						{
							break;
						}
						else
						{
							if(input[lastWhiteSpace] == '!')
								previousCommandFlag = 1;
							if(input[lastWhiteSpace] == '&')
								parallelFlag = 1;

							args[j][currentIndex] = input[lastWhiteSpace];
							printf("copying char: \'%c\'\n",input[lastWhiteSpace]);
							printf("args[j]: \'%s\'\n", args[j]);
							lastWhiteSpace++;
							currentIndex++;
						}
					}
					
					j++;
				}
				i++;
				
			}
			lastWhiteSpace = currentIndex = 0;
			//input parsed and put into history
			printf("args[0] right before history: \'%s\'\n",args[0]);
			history[historyCount] = args; //putting command in history
			printf("history after being given args: \'%s\'\n' ", history[historyCount][0]); 
			historyCount++; //incrementing historyCounter
			fflush(stdout);
			errno = 0;

			pid_t pid = fork();
			if(pid == 0)
			{
				if(previousCommandFlag)
				{
					printf("previousCommandFlag triggered");
					i = 2;
					args = history[historyCount - 2];
					printf("history[historyCount-1][0]: %s\n", history[historyCount - 2][0]);
					while(args[0][0] == '!' && historyCount - i >= 0)
					{
						printf("in previousCommandFlag while loop");
						if(args[0][0] == '!')
						{
							if(args[0][1] != '!')
							{
								int commandNumber = args[0][1] - '0'; 
								args = history[commandNumber + 1];
								break;
							}
							else
							{
								args = history[historyCount - i];
								i++;
							}
						}
					}
				}	
				previousCommandFlag = 0;
				printf("in fork\n");
				printf("%s args[0]\n", args[0]);
				printf("%s args[1]\n", args[1]);
				execvp(args[0], args);
				switch(errno)
				{
					case 0:
					printf("no error\n");
					break;
					case E2BIG:
					printf("E2BIG\n");
					break;
					case EACCES:
					printf("EACCES\n");
					break;
					case EFAULT:
					printf("EFAULT\n");
					break;
					case EINVAL:
					printf("EINVAL\n");
					break;
					case EIO:
					printf("EIO\n");
					break;
					case EISDIR:
					printf("EISDIR\n");
					break;
					case ELIBBAD:
					printf("ELIBBAD\n");
					break;
					case ELOOP:
					printf("ELOOP\n");
					break;
					case EMFILE:
					printf("EMFILE\n");
					break;
					case ENFILE:
					printf("ENFILE\n");
					break;
					case ENAMETOOLONG:
					printf("ENAMETOOLONG\n");
					break;
					case ENOENT:
					printf("ENOENT\n");
					break;
					case ENOMEM:
					printf("ENOMEM\n");
					break;
					case ENOEXEC:
					printf("ENOEXEC\n");
					break;
					case ENOTDIR:
					printf("ENOTDIR\n");
					break;
					case EPERM:
					printf("EPERM\n");
					break;
					case ETXTBSY:
					printf("ETXTBSY\n");
					break;
					default:
					printf("unknown error\n");
					break;	
				};
				return 0;	
			}
			previousCommandFlag = 0;
			if(!parallelFlag)	
				wait();
		}
		else
		{
			should_run = 0; 
		}
	}
return 0;
}