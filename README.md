# minishell

This minishell ignores SIGINT, SIGQUIT(CONTROL '\'), SISTSTP(CONTROL Z) like 'BASH shell'.

You can use pipe.
	ex) ls | wc -l
	1. check there is pipe command or not
	2. If there is pipe command, make child process
	3. execution

you can use redirection

If you want to exit minishell, input 'exit'

possible to background process. In that case, I input 'sleep 5 &' and ps -l.I can see zombi. To solve this problem, I use Signalhandler.


