#include "response.h"
#include "string.h"
#include <stdio.h>

int response_size(Response *self) {
    printf("Response size\n");
    return strlen(self->body);
}

void response_init(Response *self) {
    printf("Response init\n");
    self->body = "";
}
