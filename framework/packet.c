#include <netinet/in.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include "time.h"
#include "packet.h"

#if 0
/*
 * Structs exported from netinet/in.h
 */

/* Internet style socket address */
struct sockaddr_in  {
  unsigned short int sin_family; /* Address family */
  unsigned short int sin_port;   /* Port number */
  struct in_addr sin_addr;	 /* IP address */
  unsigned char sin_zero[...];   /* Pad to size of 'struct sockaddr' */
};
#endif

// @TODO:
/* Implements packet format checks
 * 1. Packet data must have ID field
 * 2. Packet must have valid flags field
 * 3. Flags field must conform to defined structure
 * 4. Check packet data fields for value overflows and allowed ranges
*/

int _packet_verify_flags_flow(PacketFlags packetFlags);
int _packet_verify_flags_type(PacketFlags packetFlags);
int _packet_verify_flags_target(PacketFlags packetFlags);
int _packet_verify_flags_action(PacketFlags packetFlags);
int _packet_verify_flags_respond(PacketFlags packetFlags);
int _packet_verify_flags_window(PacketFlags packetFlags);
int _packet_verify_flags_config(PacketFlags packetFlags);
int _packet_verify_flags_init(PacketFlags packetFlags);

char *pack_json(Packet *packet) {
    char *packed = NULL;
    return packed;
}

int unpack_json(char *packed, Packet *destPacket) {
    return 0;
}

char *pack_binary(Packet *packet) {
    char *packed = NULL;
    return packed;
}

int unpack_binary(char *packed, Packet *destPacket) {
    return 0;
}

int packet_verify(const Packet *packet) {
    int result = 1;
    result *= packet_verify_id(packet);
    result *= packet_verify_flags(packet);
    result *= packet_verify_request_address(packet);
    result *= packet_verify_response_address(packet);
    if (packet->data_window_start) {
        result *= packet_verify_data_window_start(packet, (unsigned long)time(NULL));
    }
    if (packet->data_window_stop) {
        result *= packet_verify_data_window_stop(packet, (unsigned long)time(NULL));
    }
    return result;
}

int packet_verify_id(const Packet *packet) {
    if (! (0 < packet->id && packet->id < 65536)) {
        // value out of range, error
        return 0;
    }
    return 1;
}

int packet_verify_flags(const Packet *packet) {
    int result = 1;
    result *= _packet_verify_flags_flow(packet->flags);
    result *= _packet_verify_flags_type(packet->flags);
    result *= _packet_verify_flags_target(packet->flags);
    result *= _packet_verify_flags_action(packet->flags);
    result *= _packet_verify_flags_respond(packet->flags);
    result *= _packet_verify_flags_window(packet->flags);
    result *= _packet_verify_flags_config(packet->flags);
    result *= _packet_verify_flags_init(packet->flags);
    return result;
}

int packet_verify_request_address(const Packet *packet) {
    struct sockaddr_in *placeholder = NULL;
    int result = inet_pton(AF_INET, packet->request_address, (void *) &placeholder);
    return 0 != result;
}

int packet_verify_response_address(const Packet *packet) {
    struct sockaddr_in *placeholder = NULL;
    int test = inet_pton(AF_INET, packet->response_address, (void *) &placeholder);
    return 0 != test;
}

int packet_verify_data_window_start(const Packet *packet, int now) {
    return packet->data_window_start < now ? 1 : 0;
}

int packet_verify_data_window_stop(const Packet *packet, int now) {
    return packet->data_window_stop < now ? 1 : 0;
}

int packet_verify_data_window_causal(const Packet *packet) {
    return packet->data_window_start <= packet->data_window_stop ? 1 : 0;
}

int _packet_verify_flags_flow(PacketFlags packetFlags) {
    if (! (0 == packetFlags.flow || 1 == packetFlags.flow)) {
        return 0;
    }
    return 1;
}

int _packet_verify_flags_type(PacketFlags packetFlags) {
    if (! (0 == packetFlags.type || 1 == packetFlags.type)) {
        return 0;
    }
    return 1;
}

int _packet_verify_flags_target(PacketFlags packetFlags) {
    if (! (0 == packetFlags.target || 1 == packetFlags.target)) {
        return 0;
    }
    return 1;
}

int _packet_verify_flags_action(PacketFlags packetFlags) {
    if (! (0 == packetFlags.action || 1 == packetFlags.action)) {
        return 0;
    }
    return 1;
}

int _packet_verify_flags_respond(PacketFlags packetFlags) {
    if (! (0 == packetFlags.respond || 1 == packetFlags.respond)) {
        return 0;
    }
    return 1;
}

int _packet_verify_flags_window(PacketFlags packetFlags) {
    if (! (0 == packetFlags.window || 1 == packetFlags.window)) {
        return 0;
    }
    return 1;
}

int _packet_verify_flags_config(PacketFlags packetFlags) {
    if (! (0 == packetFlags.config || 1 == packetFlags.config)) {
        return 0;
    }
    return 1;
}

int _packet_verify_flags_init(PacketFlags packetFlags) {
    if (! (0 == packetFlags.init || 1 == packetFlags.init)) {
        return 0;
    }
    return 1;
}
