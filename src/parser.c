#include "dshell.h"

#define DSH_TOK_BUFSIZE 64
#define DSH_TOK_DELIM " \t\r\n"

char **dshell_split_line(char *line)
{
    int bufsize = DSH_TOK_BUFSIZE;
    int position = 0;
    char **tokens = malloc(bufsize * sizeof(char *));
    char *token;

    if (!tokens) {
        perror("dshell");
        exit(EXIT_FAILURE);
    }

    token = strtok(line, DSH_TOK_DELIM);
    while (token) {
        tokens[position++] = token;

        if (position >= bufsize) {
            bufsize += DSH_TOK_BUFSIZE;
            tokens = realloc(tokens, bufsize * sizeof(char *));
            if (!tokens) {
                perror("dshell");
                exit(EXIT_FAILURE);
            }
        }

        token = strtok(NULL, DSH_TOK_DELIM);
    }

    tokens[position] = NULL;
    return tokens;
}

