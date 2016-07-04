#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include "minishell.h"
#define MAXLINE 255

int main(void)
{
	char line[MAXLINE];
	int i;
	char ** arglist;

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
