#ifndef DSHELL_H
#define DSHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

/* Core loop */
void dshell_loop(void);

/* Input */
char *dshell_read_line(void);
char **dshell_split_line(char *line);

/* Execution */
int dshell_execute(char **args);
int dshell_launch(char **args);

/* Utils */
void dshell_banner(void);

#endif
