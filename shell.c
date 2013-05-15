#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>

#define MAX_BUFF 1024
#define MAX_ARR  1024

char *scripts[] = {"archivos.sh", "informacion_sistema.sh","logs.sh",
    "paquetes.sh", "procesos.sh", "usuarios.sh"};
int scripts_len = 6;

void parse_args(char *buffer, char **args,
        size_t args_size, size_t *num_args, char *sep_str);

void exec_cmd(char *arg)
{
    char *args[MAX_ARR];
    size_t num_args;
    parse_args(arg, args, MAX_ARR, &num_args, " \t\n");
    if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
        exit(0);
    int i;
    pid_t pid;
    int *status;
    char *buf[MAX_BUFF];
    buf[0] = arg;
    for (i = 0; i < scripts_len; i++) {
        if (!strcmp(args[0], scripts[i])) {
            pid = fork();
            if (pid) {
                pid = wait(status);
            } else { 
                if(execvp(args[0], args)) {
                    puts(strerror(errno));
                    exit(127);
                }
            }
        }
    }
}

void exec_shell_mode()
{
    char buff[MAX_BUFF];
    size_t num_args;
    char *args[MAX_ARR];

    while (1) {
        printf(">> ");
        fgets(buff,MAX_BUFF, stdin);
        buff[strlen(buff) - 1] = 0;
        if (buff) {
            parse_args(buff, args, MAX_ARR, &num_args, ";");
            size_t i;
            for (i = 0; i < num_args; i++) {
                exec_cmd(args[i]);
            }
        }
    }
}

void exec_batch_mode(char *argv[], int argc)
{
    char buff[MAX_BUFF]; 
    buff[0] = 0;
    int offset = 0;
    while (argv++, --argc) {
        int next_to_write = MAX_BUFF - offset;
        int written = snprintf(buff + offset, next_to_write, "%s ",*argv);
        if (next_to_write < written)
            break;
        offset += written;
    }
    
    char *args[MAX_ARR];
    size_t num_args;
    parse_args(buff, args, MAX_ARR, &num_args, ",");
    size_t i;
    for (i = 0; i < num_args; i++)
        exec_cmd(args[i]);
}

void parse_args(char *buffer, char **args,
        size_t args_size, size_t *num_args, char *sep_str)
{
    char **temp;
    char *buf_args[args_size];
    size_t i, j;
    args[0] = buffer;
    buf_args[0] = buffer;

    for (temp = buf_args; (*temp = strsep(&buffer, sep_str)) != NULL;) {
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
    else
        exec_batch_mode(argv, argc);
    return 0;
}
