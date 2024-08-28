#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>





int main(){
	pid_t pid;
	char bin[6], command[15], buffer[10];
	char* argv[3];

	strcpy(bin, "/bin/");

	while(1){
		printf("kk> ");
		memset(command, 0, sizeof(command));
		fgets(buffer, sizeof(buffer), stdin);
		
		if (buffer[strlen(buffer) - 1] == '\n') {
 			   buffer[strlen(buffer) - 1] = '\0';
		} 

		strcpy(command, bin);
		strcat(command, buffer);
		
		pid = fork();
		if(pid == -1){
			perror("fork() failed");
		}

		else if(pid == 0){
			argv[0] = command;
			argv[1] = "shell2.c";
			argv[2] = NULL;
			if(execve(command, argv, NULL) == -1){
				perror("execve() failed.");
			}

		}

		// Wait for avoiding the creation of zombie processes
		else{
			wait(NULL);

		}
		
	}


	return 0;

}
