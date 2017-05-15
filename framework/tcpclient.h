#include <netinet/in.h>
#include "configuration.h"

#ifndef DNA_TCP_CLIENT
#define  DNA_TCP_CLIENT


void tcp_connect_to_socket(void * receive_buffer, int socket_resource, struct sockaddr_in serverAddress);
int tcp_get_socket();
void tcp_write_message(void * receive_buffer, int socket_resource);
void tcp_read_response(void * receive_buffer, int socket_resource);
void tcp_send_message(void * receive_buffer, struct sockaddr_in serverAddress);
void* tcp_client(Task *task);

#endif