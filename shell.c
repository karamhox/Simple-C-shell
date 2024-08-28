#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>




int main(int argc, char* argv){
	pid_t pid;
	
	pid = fork();


	// Child is running
	if(pid == 0){
		printf("Running in Child Process %d\n", getpid());
		//execlp("ls", "ls", NULL);
		system("ls");
	}

	else if(pid < 0){
		printf("fork() failed\n");
	}

	else{
		wait(NULL);
		printf("Running in Parent Process %d\n", getpid());
	}








	return 0;
}
