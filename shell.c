#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_BUFF 1024
#define MAX_ARR  1024

struct Command
{
    char *description;
    char *name;
};

void parse_args(char *buffer, char **args,
        size_t args_size, size_t *num_args);

void exec_shell_mode()
{
    char buff[MAX_BUFF];
    size_t num_args;
    char *args[MAX_ARR];

    while (1) {
        printf(">>");
        fgets(buff,MAX_BUFF, stdin);
        buff[strlen(buff) - 1] = 0;
        parse_args(buff, args, MAX_ARR, &num_args);
    }
}

void parse_args(char *buffer, char **args,
        size_t args_size, size_t *num_args)
{
    char **temp;
    char *buf_args[args_size];
    size_t i, j;
    args[0] = buffer;

    for (temp = buf_args; (*temp = strsep(&buffer, "; \n\t")) != NULL;) {
        if ((*temp != '\0') && (++temp >= &buf_args[args_size]))
                break;
    }

    for (i=j=0; buf_args[i] != NULL; i++) {
        if (strlen(buf_args[i]) > 0)
            args[j++] = buf_args[i];
    }

    *num_args = j;
    args[j] = NULL;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
        exec_shell_mode();

    return 0;
}
