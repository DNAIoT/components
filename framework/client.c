#include <stdio.h>
#include "tcpclient.h"
#include "udpclient.h"

#define BUFFER_SIZE 255

int main(int argc, char **argv) {

    char buffer[BUFFER_SIZE];

    printf("Select networking protocol [1]:\n");
    printf("\t1. TCP\n");
    printf("\t2. UDP\n");

    fgets(buffer, BUFFER_SIZE, stdin);

    char *protocol = malloc(sizeof(*protocol));
    strcpy(*protocol, buffer);

    printf("Bind to [127.0.0.1]:\n");

    fgets(buffer, BUFFER_SIZE, stdin);

    char *host = malloc(sizeof(*host));
    strcpy(*host, buffer);

    printf("Use port [9879]:\n");

    fgets(buffer, BUFFER_SIZE, stdin);

    char *port = malloc(sizeof(*port));
    strcpy(*port, buffer);

    return 0;

}