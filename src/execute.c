#include "dshell.h"
#include "builtins.h"

int dshell_launch(char **args)
{
    pid_t pid = fork();
    int status;

    if (pid == 0) {
        if (execvp(args[0], args) == -1)
            perror("dshell");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("dshell");
    } else {
        do {
            waitpid(pid, &status, WUNTRACED);
        } while (!WIFEXITED(status) && !WIFSIGNALED(status));
    }

    return 1;
}

int dshell_execute(char **args)
{
    if (!args[0])
        return 1;

    for (int i = 0; i < dshell_num_builtins(); i++) {
        if (strcmp(args[0], builtin_str[i]) == 0)
            return (*builtin_func[i])(args);
    }

    return dshell_launch(args);
}

