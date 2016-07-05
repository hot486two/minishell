#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<signal.h>

int is_background(char **arg)
{
	int i;
	for(i=0;arg[i];i++)
	{
		if(!strcmp(arg[i],"&"))
		{
			arg[i]=NULL;
			return 1;
		}
	}
	return 0;
}

int is_pipe(char **arg)
{	
	int i;
	for(i=0;arg[i];i++)
	{
		if(strcmp(arg[i],"|")==0)
		{	
			arg[i]=NULL;
			return i;
		}
	}
	return 0;
}

void exec_command(char **arg)
{
	pid_t pid;

	int background_flag=0;

	int pd[2],index;//for pipe

	if(is_background(arg))
	{
		background_flag=1;
	}

	switch(pid=fork())
	{
	case -1:	//failure
		perror("fork");
		exit(1);
		//return;
		break;
	case 0:		//child process

		//child process inherited a signal handler, so set default value
		signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		signal(SIGTSTP, SIG_DFL);

		//check pipe
		if(index=is_pipe(arg))
		{
			pipe(pd);
			switch(fork())
			{
			case -1:
				perror("fork in pipe");
				return;
				break;
			case 0:
				close(pd[0]);
				dup2(pd[1],1);
				execvp(arg[0],arg);
				//execvp(arg[index-1],&arg[index-1]);
				perror("execvp");
				exit(1);
				break;
			default:
				close(pd[1]);
				dup2(pd[0],0);
				execvp(arg[index+1],&arg[index+1]);
				perror("execvp");
				exit(1);
				break;
			}
		}
		else
		{
			redirectin(arg);
			redirectout(arg);
			redirecterr(arg);
	
			execvp(arg[0], arg);
			perror("execvp");
			exit(1);
		}
		break;
	default:	//parent process
		if(background_flag == 0)
		{
			waitpid(pid, NULL, 0);
		}
		break;
	}
}
