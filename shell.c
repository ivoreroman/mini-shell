#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_BUFF 1024
#define MAX_ARR  1024

// Lista de comandos validos
char *scripts[] = {"archivos.sh", "informacion_sistema.sh","logs.sh",
    "paquetes.sh", "procesos.sh", "usuarios.sh", "help.sh"};
int scripts_len = 7;

void parse_args(char *buffer, char **args,
        size_t args_size, size_t *num_args, char *sep_str);
void exec_file_cmd(char *filename);


// Ejecucion del comando 
void exec_cmd(char **args) 
{
    int i;
    pid_t pid;
    int *status;

    // Se itera la lista de comandos basicos
    // para comprobrar si hay algun comando valido
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
            break;
        }
    }
    if (i == scripts_len)
        perror("No existe el comando");
}

// Ejecuta un comando en modo shell
void exec_cmd_shell(char *arg)
{
    char *args[MAX_ARR];
    size_t num_args = 0;

    // Retira espacios en blancos
    parse_args(arg, args, MAX_ARR, &num_args, " \t\n");
    if (!num_args)
        return;

    // Busca las palabras de salida para quitar la aplicacion
    if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit"))
        exit(0);
    
    // Ejecucion del comando
    exec_cmd(args);
}

// Ejecuta modo shell
void exec_shell_mode()
{
    char buff[MAX_BUFF];
    size_t num_args;
    char *args[MAX_ARR];

    // Ciclo infinito que terminara mediante un comando
    while (1) {
        printf(">> ");
        // obtiene input desde entrada estandar
        fgets(buff,MAX_BUFF, stdin);
        buff[strlen(buff) - 1] = 0;

        if (buff) {
            // Se separan comandos por ';'
            parse_args(buff, args, MAX_ARR, &num_args, ";");
            size_t i;

            // Se ejecuta cada comando
            for (i = 0; i < num_args; i++) {
                exec_cmd_shell(args[i]);
            }
        }
    }
}

// Se ejecuta un comando en modo batch
void exec_cmd_batch(char *arg)
{
    char *args[MAX_ARR];
    size_t num_args = 0;

    // Se retiran espacios en blancos
    parse_args(arg, args, MAX_ARR, &num_args, " \t\n");

    // Si esta vacio, sale
    if (!num_args)
        return;

    // Termina si encuentra quit o exit
    if (!strcmp(args[0], "quit") || !strcmp(args[0], "exit")) {
        fclose(stdout);
        exit(0);
    }

    // Al encontrar -o la salida estandar se redirecciona a un archivo
    if (!strcmp(args[0], "-o")) {
        int fd = open(args[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 1);
        return;
    }

    // Al encontrar -e, redirige el stderr se redireccion a un archivo
    if (!strcmp(args[0], "-e")) {
        int fd = open(args[1], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
        dup2(fd, 2);
        return;
    }

    // Al encontrar -f, lee comandos desde un archivo dado
    if (!strcmp(args[0], "-f")) {
        exec_file_cmd(args[1]);
        return;
    }

    exec_cmd(args);
}

// Ejecuta los comandos desde un archivo dado
void exec_file_cmd(char *filename)
{
    // Se abre el archivo y si no existe termina
    FILE *file = fopen(filename, "r");
    char *str[MAX_BUFF];
    char *args[MAX_ARR];
    size_t num_args;
    if (!file) {
        perror("Archivo no encontrado");
        return;
    }

    // Se lee linea por linea del archivo y se
    // ejecuta cada batch de comandos
    while (fgets(str, MAX_BUFF, file) != NULL) {
        parse_args(str, args, MAX_ARR, &num_args, ";");
        size_t i;
        for (i = 0; i < num_args; i++) {
            if (!num_args)
                continue;
            exec_cmd_shell(args[i]);
        }
    }
    fclose(file);
}

// Ejecucion en modo batch, recibe los argumentos de terminal
void exec_batch_mode(char *argv[], int argc)
{
    // De los argumentos de consola se crea un solo string
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
    
    // Los comandos van separados por comas, por lo que se obtiene cada comando
    // y se depositan en un arreglo
    char *args[MAX_ARR];
    size_t num_args;
    parse_args(buff, args, MAX_ARR, &num_args, ",");
    size_t i;

    // Se ejecuta cada comando 
    for (i = 0; i < num_args; i++)
        exec_cmd_batch(args[i]);
}

// A partir de un string de origen y de un string separador se obtiene
// un arreglo de strings separados por ese string, ademas de la longitud
void parse_args(char *buffer, char **args,
        size_t args_size, size_t *num_args, char *sep_str)
{
    char **temp;
    char *buf_args[args_size];
    size_t i, j;
    args[0] = buffer;
    buf_args[0] = buffer;

    // El string buffer se modifica y temp sirve como iterador
    for (temp = buf_args; (*temp = strsep(&buffer, sep_str)) != NULL;) {
        if ((*temp != '\0') && (++temp >= &buf_args[args_size]))
                break;
    }

    // Se van asignando valores al arreglo
    for (i=j=0; buf_args[i] != NULL; i++) {
        if (strlen(buf_args[i]) > 0)
            args[j++] = buf_args[i];
    }

    // Al final se da valor al contador
    *num_args = j;
    args[j] = NULL;
}

int main(int argc, char *argv[])
{
    // Si no hay argumentos correra como shell, de lo contrario en batch
    if (argc < 2)
        exec_shell_mode();
    else {
        exec_batch_mode(argv, argc);
    }
    return 0;
}
