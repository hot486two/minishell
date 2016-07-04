#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void exec_command(char **arg)
{
	pid_t pid;

	switch(pid=fork())
	{
	case -1:	//failure
		perror("fork");
		return;
		break;
	case 0:		//child process
		execvp(arg[0], arg);
		perror("execvp");
		exit(1);
		break;
	default:	//parent process
		waitpid(pid, NULL, 0);
		break;
	}
}
