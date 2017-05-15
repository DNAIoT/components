#include "request.h"
#include "string.h"
#include <stdio.h>

int request_size(Request *self){
    printf("Request size\n");
    return strlen((*self).body);
}

void request_init(Request *self) {
    printf("Request init\n");
    self->body = "";
}