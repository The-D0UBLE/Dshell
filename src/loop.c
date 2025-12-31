#include "dshell.h"

void dshell_loop(void)
{
    char *line;
    char **args;
    int status;

    do {
        printf("dshell> ");
        line = dshell_read_line();
        args = dshell_split_line(line);
        status = dshell_execute(args);

        free(line);
        free(args);
    } while (status);
}
