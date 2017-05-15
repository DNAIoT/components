#include "request.h"
#include "response.h"
#include "configuration.h"
#include "eventloop.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define CONFIG_BUFFER_LENGTH 255
#define CONFIG_TOKEN "="

int ServiceAgentDeviceConfiguration(char* path, char* mode, Device *device) {

    FILE *handle;
    char buffer[CONFIG_BUFFER_LENGTH];
    char *key, *value;

    handle = fopen(path, mode);

    if (!handle) {
        return 0;
    }

    while(!feof(handle)) {
        fgets(buffer, CONFIG_BUFFER_LENGTH, handle);
        key = NULL;
        value = NULL;
        key = strtok(buffer, CONFIG_TOKEN);
        value = strtok(NULL, "\n");
        if (key == NULL || value == NULL) {
            continue;
        }
        if (strcmp(key, "host") == 0) {
            device->host = malloc(sizeof(value));
            strcpy(device->host, value);
        } else if (strcmp(key, "port") == 0) {
            device->port = atoi(value);
        } else if (strcmp(key, "endpoint") == 0) {
            device->endpoint = malloc(sizeof(value));
            strcpy(device->endpoint, value);
        } else {
            continue;
        }
    }

    return 1;

}

void ServiceAgentStart() {
    //
}