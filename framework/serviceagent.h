#ifndef DNA_SERVICE_AGENT
#define  DNA_SERVICE_AGENT

#include "configuration.h"

int ServiceAgentDeviceConfiguration(char* path, char* mode, Device *device);

struct ServiceAgent {
    void (*start) ();
    void (*stop) ();
};

typedef struct ServiceAgent ServiceAgent;

#endif