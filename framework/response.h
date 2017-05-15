#ifndef DNA_RESPONSE
#define  DNA_RESPONSE

struct Response {
    char *hostname;
    int port;
    char *status;
    char *body;
    int (*init) (struct Response *);
};

typedef struct Response Response;

int response_size(Response *self);
void response_init(Response *self);

#endif