#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<signal.h>
#include "minishell.h"
#define MAXLINE 255

int main(void)
{
	char line[MAXLINE];
	int i;
	char ** arglist;

	struct sigaction act;

	signal(SIGINT, SIG_IGN);	
	signal(SIGQUIT, SIG_IGN);
	signal(SIGTSTP, SIG_IGN);

	act.sa_handler = child_handler;
	sigfillset(&act.sa_mask);
	act.sa_flags = SA_RESTART;
	sigaction(SIGCHLD,&act,NULL);



	fputs("minishell> ",stdout);

	while(fgets(line,MAXLINE,stdin))
	{
		if(!strncmp(line,"exit",4))
		{
			exit(0);
		}

		if(arglist=command_parse(line))
		{
			if(!check_builtin(arglist))
			{
//				for(i=0;arglist[i];i++)
//				{
				//	printf("[%d] : %s\n", i,arglist[i]);
					exec_command(arglist);
//				}
			}	
			command_freelist(arglist);
		}

		fputs("minishell> ",stdout);
	}
	return 0;
}
