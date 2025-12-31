#include "dshell.h"

#define DSH_RL_BUFSIZE 1024

char *dshell_read_line(void)
{
    int bufsize = DSH_RL_BUFSIZE;
    int position = 0;
    char *buffer = malloc(bufsize);
    int c;

    if (!buffer) {
        perror("dshell");
        exit(EXIT_FAILURE);
    }

    while (1) {
        c = getchar();

        if (c == EOF || c == '\n') {
            buffer[position] = '\0';
            return buffer;
        }

        buffer[position++] = c;

        if (position >= bufsize) {
            bufsize += DSH_RL_BUFSIZE;
            buffer = realloc(buffer, bufsize);
            if (!buffer) {
                perror("dshell");
                exit(EXIT_FAILURE);
            }
        }
    }
}

