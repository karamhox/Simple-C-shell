#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>


void executeCommand(char command[], char* argv[], char flags[]){
        argv[0] = command;
	if(strlen(flags) == 0){
		argv[1] = NULL;
	}
	else{
		argv[1] = flags;
	}
	argv[2] = NULL;
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



void checkFlags(char* flags, size_t fsize, char* command, size_t csize){
	int x = 0;
	for(int i = 0; i < csize; i++){
		if(command[i] == '-'){
			command[i-1] = '\0';
			for(int j = i; j < fsize + i; j++){
				if(command[j] == '\0'){
					return;
				}
				flags[x] = command[j];
				command[j] = '\0';
				x++;
			}
		}
	}
}


int main(){
	pid_t pid;
	char bin[6], command[15], buffer[10], flags[10];
	char* argv[3];

	strcpy(bin, "/bin/");

	while(1){
		printf("kk> ");
		memset(command, 0, sizeof(command));	
		memset(flags, 0, sizeof(flags));
		getInput(buffer, sizeof(buffer));
		strcpy(command, bin);
		strcat(command, buffer);
		checkFlags(flags, sizeof(flags), command, sizeof(command));	

		pid = fork();
		if(pid == -1){
			perror("fork() failed");
		}

		else if(pid == 0){
			executeCommand(command, argv, flags);

		}

		// Wait for avoiding the creation of zombie processes
		else{
			wait(NULL);

		}
		
	}


	return 0;

}
