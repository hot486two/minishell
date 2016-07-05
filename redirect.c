#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

void redirectout(char **arg)
{
	int i, fd;
	for(i=0;arg[i];i++)
	{
		if((strcmp(arg[i],"1>")==0) ||( strcmp(arg[i],">")==0))
		{
			if((fd=open(arg[i+1],O_WRONLY|O_CREAT|O_TRUNC,0644))==-1)
			{
				perror("open");
				return;
			}
			if(dup2(fd,1)==-1)
			{
				perror("dup2 error");
				return;
			}
			close(fd);
			arg[i]=NULL;
			break;
		}
	}
}

void redirectin(char** arg)
{
	int i,fd;
	for(i=0;arg[i];i++)
	{
		if((strcmp(arg[i],"0<")==0) || (strcmp(arg[i],"<")==0))
		{
			if((fd=open(arg[i+1],O_RDONLY))==-1)
			{
				perror("open");
				return;
			}
			dup2(fd,0);
			close(fd);
			arg[i]=NULL;
			break;

		}

	}
}
void redirecterr(char** arg)
{
	int i,fd;
	for(i=0;arg[i];i++)
	{
		if((strcmp(arg[i],"2>"))==0)
		{
			if((fd=open(arg[i+1],O_WRONLY|O_CREAT|O_TRUNC,0644))==-1)
			{
				perror("open");
				return;
			}
			dup2(fd,2);
			close(fd);
			arg[i]=NULL;
			break;
		}
	}
}
