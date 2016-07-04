#include<stdio.h>
#include<sys/utsname.h>
#include<pwd.h>
#include "minishell.h"

//builtin command list

BT_TYPE bt_array[] = {
	"hostname",hostname_func,NULL,NULL
};

// check that input command is builtin command or not
int check_builtin(char **arglist)
{
	int i;
	for(i=0;bt_array[i].cmd;i++)
	{
		if(!strcmp(bt_array[i].cmd,arglist[0]))
		{
			bt_array[i].bt_func(arglist);//call the builtin_function
			return 1;//return 1 if input command is builtin command
		}
	}
	return 0;	//return 0 if input command is not builtin command
}

// get linux system information and output a hostname from nodename member
void hostname_func(char **arg)
{
	struct utsname hostinfo;

	if(uname(&hostinfo)==-1)
	{
		perror("uname");
		return ;
	}
	printf("hostname : %s\n", hostinfo.nodename);
}
