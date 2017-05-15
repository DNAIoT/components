#include <netinet/in.h>
#include "configuration.h"

#ifndef DNA_UDP_SERVER
#define  DNA_UDP_SERVER

int udp_get_socket();
void udp_write_message(void * receive_buffer, int socket_resource, struct sockaddr_in serverAddress);
void udp_read_response(void * receive_buffer, int socket_resource, struct sockaddr_in serverAddress);
void udp_send_message(void * receive_buffer, struct sockaddr_in serverAddress);
void* udp_client(Task *task);

#endif