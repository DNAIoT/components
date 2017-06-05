
typedef struct Packet Packet;
typedef struct PacketFlags PacketFlags;

// 4 bytes structure
// packed to 2 bytes of flags for sending
struct PacketFlags {
    // 0 : no flow control
    // 1 : flow control
    unsigned int flow : 1;
    // 0 : request
    // 1 : response
    unsigned int type : 1;
    // 0 : service
    // 1 : device
    unsigned int target : 1;
    // 0 : read
    // 1 : write
    unsigned int action : 1;
    // 0 response not required
    // 1 response required
    unsigned int respond : 1;
    // 0 : time window not supported
    // 1 : time window supported
    unsigned int window : 1;
    // 0 : not a config message
    // 1 : config message
    unsigned int config : 1;
    // 0 : not init message
    // 1 : init message
    unsigned int init : 1;
};

struct Packet {
    // 2 byte int
    int id;
    // flags struct
    PacketFlags *flags;
    // 6 bytes : ip/port
    char *request_address;
    // 6 bytes : ip/port
    char *response_address;
    // 8 bytes : time
    // pack to 6 bytes
    unsigned int data_window_start;
    // 8 bytes : time
    // pack to 6 bytes
    unsigned int data_window_stop;
    char *payload;
};

char *pack(Packet *packet);
Packet *unpack(char *packed);
int packet_verify(Packet *packet);
int packet_verify_id(Packet *packet);
int packet_verify_flags(Packet *packet);
int packet_verify_request_address(Packet *packet);
int packet_verify_response_address(Packet *packet);
int packet_verify_data_window_start(Packet *packet, int now);
int packet_verify_data_window_stop(Packet *packet, int now);
int packet_verify_data_window_causal(Packet *packet);