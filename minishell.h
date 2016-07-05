#ifndef MINISHELL_H_
#define MINISHELL_H_

char** command_parse(char*line);
void command_freelist(char**arglist);

void hostname_func(char **);
int check_builtin(char**);

typedef struct bt_type{
    char *cmd;
    void (*bt_func)(char **);
} BT_TYPE;

void exec_command(char **arg);

void child_handler(int signo);



#endif /* MINISHELL_H_ */
