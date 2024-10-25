#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>





#define SIZE 10


char* getInput(char* buffer){
	int i = 0;
	char c;
	int size = SIZE - 5;

	char* command = (char *)malloc(SIZE);
	strcpy(command, "/bin/sh");

	while(i < size){
		c = getc(stdin);
		
		if(c == '\n'){
			c = '\0';
			break;
		}

		command = (char *)realloc((void *)command, size + sizeof(char));
		*(command + sizeof(char) * i + 5) = c;

		size++;
		i++;	
	}

	return command; 
}


int argvSize = 2;
char** parseargv(char* command){
	char** argv = (char **)malloc(argvSize * sizeof(char *));

	argv[0] = strtok(command, " ");
	int i = 1;
	
	while(1){
		argv[i] = strtok(NULL, " ");
		if(argv[i] == NULL){
			argvSize --;
			break;
		}

		argvSize ++;
		argv = (char **)realloc((void *)argv, argvSize * sizeof(char *));
		
		i++;

	}

	return argv;
}


void execCommand(char** argv){
	if(execve(argv[0], argv, NULL) == -1){
		perror("execve()");
	}
}


int main(){
	char* command;
	char** argv;
	pid_t pid;


	while(1){
		printf(">>> ");
		command = getInput(command+5);
		argv = parseargv(command);

		pid = fork();

		switch(pid){
			case 0:
				execCommand(argv);
			case -1:
				perror("fork()");
			default:
				wait(NULL);

		}
	}


	return 0;
}

