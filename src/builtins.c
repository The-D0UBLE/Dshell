#include "dshell.h"
#include "builtins.h"

char *builtin_str[] = {
    "cd",
    "help",
    "exit",
    "dsay"
};

int (*builtin_func[])(char **) = {
    dshell_cd,
    dshell_help,
    dshell_exit,
    dshell_dsay
};

int dshell_num_builtins(void)
{
    return sizeof(builtin_str) / sizeof(char *);
}

/* Builtins */

int dshell_cd(char **args)
{
    if (!args[1]) {
        fprintf(stderr, "dshell: expected argument to cd\n");
    } else if (chdir(args[1]) != 0) {
        perror("dshell");
    }
    return 1;
}

int dshell_help(char **args)
{
    (void)args;
    printf("Dshell – custom command shell\n");
    printf("Builtins:\n");

    for (int i = 0; i < dshell_num_builtins(); i++)
        printf("  %s\n", builtin_str[i]);

    return 1;
}

int dshell_exit(char **args)
{
    (void)args;
    return 0;
}

/* Example custom command */
int dshell_dsay(char **args)
{
    (void)args;
    printf("Dshell says hello \n");
    return 1;
}

