#ifndef DNA_REQUEST
#define  DNA_REQUEST

struct Request {
    char *hostname;
    int port;
    char *status;
    char *body;
    int (*init) (struct Request *);
};

typedef struct Request Request;

int request_size(Request *self);
void request_init(Request *self);

#endif