/*
 * tcpclient.c - A simple TCP client
 * usage: tcpclient <host> <port>
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include "tcpclient.h"
#include "configuration.h"

#define BUFFER_SIZE 8192

#if 0

/*
 * Struct exported from netdb.h
 */

/* Domain name service (DNS) host entry */
struct hostent {
  char    *h_name;        /* official name of host */
  char    **h_aliases;    /* alias list */
  int     h_addrtype;     /* host address type */
  int     h_length;       /* length of address */
  char    **h_addr_list;  /* list of addresses */
}
#endif

void tcp_connect_to_socket(void * receive_buffer, int socket_resource, struct sockaddr_in serverAddress) {
    if (connect(socket_resource, (struct sockaddr *) &serverAddress, sizeof(serverAddress)) < 0) {
        printf("Error connecting to server\n");
        printf("Receive buffer: %s (socket: %d)\n", (char *) receive_buffer, socket_resource);

        close(socket_resource);
        exit(0);
    }
    printf("Connection successful!\n");
}

int tcp_get_socket() {
    int socket_resource;
    socket_resource = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_resource < 0) {
        printf("Error acquiring socket\n");
        exit(0);
    }
    printf("Socket acquired\n");
    return socket_resource;
}

void tcp_write_message(void * receive_buffer, int socket_resource) {
    int message_length;
    message_length = write(socket_resource, receive_buffer, BUFFER_SIZE);
    if (message_length < 0) {
        printf("Error sending message (%d)\n", message_length);

        close(socket_resource);
        exit(0);
    }
    printf("Message sent\n");
}

void tcp_read_response(void * receive_buffer, int socket_resource) {
    int message_length;
    bzero(receive_buffer, BUFFER_SIZE);
    message_length = read(socket_resource, receive_buffer, BUFFER_SIZE);
    if (message_length < 0) {
        printf("Error reading server response\n");

        close(socket_resource);
        exit(0);
    }
}

void tcp_send_message(void * receive_buffer, struct sockaddr_in serverAddress) {

    int socket_resource;

    socket_resource = tcp_get_socket();
    tcp_connect_to_socket(receive_buffer, socket_resource, serverAddress);
    tcp_write_message(receive_buffer, socket_resource);
    tcp_read_response(receive_buffer, socket_resource);

    printf("Server response a: %s\n", receive_buffer);
    close(socket_resource);
}

// replace argc & argv with a structure containing same information
void* tcp_client(Task * task) {
    int port, message_count = 1, thread_count = 1;
    struct sockaddr_in serverAddress;
    struct hostent *host;
    char *hostname;
    char receive_buffer[BUFFER_SIZE];

    if (!task->host || !task->port) {
        printf("Usage: client <hostname> <port> [<message> [message_count] [thread_count]]\n");
        exit(0);
    }

    hostname = task->host;
    port = atoi(task->port);

    if (port < 2000 || port > 65535) {
        printf("Illegal port number [allowed range: 2000 - 65535]\n");
        exit(0);
    }

    host = gethostbyname(hostname);

    if (NULL == host) {
        printf("Error getting host\n");
        exit(0);
    }
    printf("Host resolved\n");

    bzero((char *) &serverAddress, sizeof(serverAddress));
    bcopy((char *) host->h_addr, (char *) &serverAddress.sin_addr.s_addr, host->h_length);
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(port);
    printf("Host configured\n");

    if (task->message) {
        if (strlen(task->message) > sizeof(receive_buffer)) {
            printf("Message too long\n");
            exit(0);
        }
        strcpy(receive_buffer, task->message);

        if (task->repeat_count > 1) {

            message_count = task->repeat_count;
            printf("Sending %d messages...\n", message_count);

            if (task->thread_count > 1) {
                thread_count = task->thread_count;
                printf("Total of %d threads requested\n", thread_count);
            }
        }

        printf("Sending %d messages...\n", message_count * thread_count);
        for (int i = 0; i < message_count; i++) {
            printf("sending...\n");
            tcp_send_message(receive_buffer, serverAddress);
        }
    }
    else {

        bzero(receive_buffer, BUFFER_SIZE);
        printf("Message: ");
        fgets(receive_buffer, BUFFER_SIZE, stdin);
        tcp_send_message(receive_buffer, serverAddress);

        printf("Server response: %s\n", receive_buffer);

    }

    return NULL;
}
