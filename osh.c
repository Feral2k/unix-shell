#include <stdio.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#define MAX_LINE 80 /* The maximum length command */

int main(void) {
	char args[MAX_LINE/2 + 1][MAX_LINE]; /* command line arguments */
	int should_run = 1; /* flag to determine when to exit program */
	char tempArgs[100];
	while (should_run) {
		printf("osh>");
		fgets(tempArgs, sizeof(tempArgs), stdin);
		int i = 0;
		int j = 0;
		int lastWhiteSpace = 0;
		int currentArgsIndex = 0;
		char* charSta3r;
		int count = 0;
		
		do
		{
		printf("\'%c\' ", tempArgs[i]);
		if(tempArgs[i] == ' ' || tempArgs[i] == '\0')
			{
				while(lastWhiteSpace < i)
				{

					if(tempArgs[lastWhiteSpace] != '\n')
					{
					printf("TA: \'%c\'" ,tempArgs[currentArgsIndex]);
						args[j][currentArgsIndex] = tempArgs[lastWhiteSpace];
						lastWhiteSpace++;
						currentArgsIndex++;
						printf("\'%s\'\n",args[j]);
					}
					else
					{
						printf("The character is a carriage return\n");
						lastWhiteSpace++;
						count++;

						//currentArgsIndex++;
					}
				}
			j++;
			currentArgsIndex = 0;
			lastWhiteSpace++;
			}
			i++;
			//printf("%i\n", i);
		}while(tempArgs[i-1] != '\0');
		
		fflush(stdout);
		errno = 0;
		printf("it's out of the while loop\n");
		printf("args[0]\'%s\'\n" , args[0]);
		char* tempCharStar[MAX_LINE/2+1];
		int iterator = 0;
		
		printf("before the while");
		while(iterator < count)
		{
			printf("while loop iterator");
			tempCharStar[iterator] = args[iterator];
			iterator++;
			printf("while loop iterator");
 		}
		pid_t pid = fork();
		if (pid == 0) {
			printf("in fork");
			execvp(tempCharStar[0], tempCharStar);
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
		wait();
		
		should_run = 0;

		/**
		* After reading user input, the steps are:
		* (1) fork a child process using fork()
		* (2) the child process will invoke execvp()
		* (3) if command included &, parent will invoke wait()
		*/
		}
	return 0;
}
