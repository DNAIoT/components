#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <math.h>

#define BUFFER_SIZE 8192

typedef struct Arg {
    int connection;
    struct sockaddr_in clientAddress;
    char message[BUFFER_SIZE];
} Arg;

#if 0
/*
 * Structs exported from netinet/in.h
 */

/* Internet address */
struct in_addr {
  unsigned int s_addr;
};

/* Internet style socket address */
struct sockaddr_in  {
  unsigned short int sin_family; /* Address family */
  unsigned short int sin_port;   /* Port number */
  struct in_addr sin_addr;	 /* IP address */
  unsigned char sin_zero[...];   /* Pad to size of 'struct sockaddr' */
};

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

void* handler(void* parameter) {

    int response = -1;
//    double r;
//    int rounded_r;
    Arg *payload = (Arg *)parameter;
    printf("Message received: %s\n", payload->message);

    response = sendto(payload->connection,
                      payload->message,
                      BUFFER_SIZE,
                      0,
                      (struct sockaddr *) &payload->clientAddress,
                      sizeof(payload->clientAddress));
    if (response < 0) {
        printf("Error sending response to client\n");
    }

//    r = drand48();
//    rounded_r = round(10 * 1000 * 1000 * r);
//    usleep(rounded_r);
//    printf("Sleep interval is %d\n", rounded_r);

    printf("Response sent to client\n");
    printf("Resource disposed\n");
    pthread_exit(0);
    return NULL;
}

int main(int argc, char **argv) {

    printf("UDP server started\n");

    // declare variables
    int port, socket_resource, optval, message_length;
    char* host, answer, line;
    char receive_buffer[BUFFER_SIZE];
    socklen_t clientAddressLength;
    struct sockaddr_in serverAddress, clientAddress;

    // assign host & port
    if (argc < 2) {
        host = "127.0.0.1";
    }
    else {
        host = argv[1];
    }
    if (argc < 3) {
        port = 9889;
    }
    else {
        port = atoi(argv[2]);
    }

    printf("Host %s listening on port %d\n", host, port);

    // acquire socket
    socket_resource = socket(AF_INET, SOCK_DGRAM, 0);
    while (socket < 0) {
        printf("Failed to open socket, retry?\n");
        gets(&answer);
        socket_resource = socket(AF_INET, SOCK_DGRAM, 0);
    }

    //this is to reuse port/socket on exit
    optval = 1;
    setsockopt(socket_resource, SOL_SOCKET, SO_REUSEADDR,
               (const void *)&optval , sizeof(int));

    // prepare & build server address
    bzero((char*) &serverAddress, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons((unsigned short)port);

    while (bind(socket_resource, (struct sockaddr *)&serverAddress, sizeof(serverAddress)) < 0)
    {
        printf("Error binding to socket resources, retry?\n");
        gets(&answer);
        if (strcmp("yes", &answer)) {
            printf("Canceled, bye! :)\n");
            return 0;
        }
    }

    printf("Socket acquired\n");

    listen(socket_resource, 5);
    printf("Listening...\n");
    clientAddressLength = sizeof(clientAddress);

    printf("Enter loop\n");

    // endless loop until exit :D
    while (strcmp(&line, "exit") != 0) {

        printf("Waiting on a connection...\n");
        message_length = recvfrom(socket_resource, receive_buffer, BUFFER_SIZE, 0, (struct sockaddr *) &clientAddress, &clientAddressLength);
        printf("Connected: %d (socket_resource ID)\n", socket_resource);

        struct hostent *hostp;
        hostp = gethostbyaddr((const char *)&clientAddress.sin_addr.s_addr,
                              sizeof(clientAddress.sin_addr.s_addr), AF_INET);
        char *hostaddrp = inet_ntoa(clientAddress.sin_addr);

        if (hostp == NULL) {
            printf("Error getting Client address\n");
        }
        printf("Client address: %s\n", hostaddrp);

        if (socket_resource < 0) {
            printf("Error accepting connection\n");
            continue;
        }
        printf("Socket acquired\n");

        Arg *argument = (Arg *) malloc(sizeof(Arg));
        //Arg *argument = NULL;
        argument->connection = socket_resource;
        argument->clientAddress = clientAddress;
        memcpy((void *)argument->message, (void *)receive_buffer, BUFFER_SIZE);

        printf("Initial string: %s\n", (char *)receive_buffer);
        printf("Assigned: %d (connection ID)\n", argument->connection);

        // dispatch handler thread
        pthread_t thread_id;
        pthread_attr_t attributes;
        pthread_attr_init(&attributes);
        pthread_create(&thread_id, &attributes, handler, argument);
        // only if blocking calls are needed
        //pthread_join(thread_id, NULL);

        //printf("Thread join executed...\n");

    }

    printf("Cleanup... exit. Bye! :)\n");
    return 0;
}