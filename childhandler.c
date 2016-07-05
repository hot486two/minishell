#include<stdio.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<unistd.h>
#include<errno.h>
#include<stdlib.h>


//terminate background process(child process)
//infinite loop ends when there is no child process anymore
void child_handler(int signo)
{
	pid_t ret_pid;
	for(;;)
	{	
		ret_pid = waitpid(0,NULL,WNOHANG);//non-block mode

		if(ret_pid==0)//there is no terminated child process that running
		{	
			printf("%s\n","start!!");
			break;
		}

		if(ret_pid==-1)
		{
			if(errno==ECHILD)//there is no child process
			{	
				break;
			}
			else
			{
				perror("waitpid");
				abort();
			}
		}
	}
}

