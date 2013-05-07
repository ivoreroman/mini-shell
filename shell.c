#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAXBUFF 1024

int main(int argc, char *argv[])
{
    char buf[MAXBUFF];

    while(1) {
        printf("-> ");
        fgets(buf, MAXBUFF, stdin);
    }
    
    return 0;
}
