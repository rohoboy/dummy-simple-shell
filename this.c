#include "shell.h"
#include <stdio.h>

int main(void)
{
    char str[] = "Hello pals!. I-am pleased to meet you";
    char *delim = ".";
    char *argv[10];
    char *token = our_strtok(str, delim);
    int i = 0;
    while (token != NULL)
    {
        printf("%s\n", token);
	argv[i] = token;
        token = our_strtok(NULL, delim);
	i++;
    }
    argv[i] = NULL;
    printf("%d\n", i);
    printf("%s\n", argv[i - 1]);

    return 0;
}







