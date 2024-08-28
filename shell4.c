#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


void executeCommand(char command[], char* argv[]){
        if(execve(command, argv, NULL) == -1){
                 perror("execve() failed.");
          }
}

void getInput(char* buffer, size_t size){
	fgets(buffer, size, stdin);
	size_t len = strlen(buffer);
	if(buffer[len-1] == '\n'){
		buffer[len-1] = '\0';
	}
}


void parseArgs(char** argv, char* command){
	char* token = strtok(command, " ");
	argv[0] = token;
	size_t size = 10;
	for(int i=1; i < size; i++){
		token = strtok(NULL, " ");
		argv[i] = token;
		if(argv[i] == NULL){
			break;
		}

	}

	argv[9] = NULL;

}





int main(){
	pid_t pid;
	char bin[6], command[0x50], buffer[0x40];
	char** argv = (char**) malloc(10 * 10);

	strcpy(bin, "/bin/");

	while(1){
		printf("kk> ");
		memset(command, 0, sizeof(command));	
		getInput(buffer, sizeof(buffer));
		strcpy(command, bin);
		strcat(command, buffer);
		parseArgs(argv, command);

		pid = fork();
		if(pid == -1){
			perror("fork() failed");
		}

		else if(pid == 0){
			executeCommand(command, argv);

		}

		// Wait for avoiding the creation of zombie processes
		else{
			wait(NULL);

		}
		
	}

	free(argv);

	return 0;

}
