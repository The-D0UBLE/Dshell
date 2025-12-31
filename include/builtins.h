#ifndef BUILTINS_H
#define BUILTINS_H

int dshell_cd(char **args);
int dshell_help(char **args);
int dshell_exit(char **args);
int dshell_dsay(char **args);

extern char *builtin_str[];
extern int (*builtin_func[])(char **);

int dshell_num_builtins(void);

#endif

