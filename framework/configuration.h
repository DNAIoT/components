#ifndef DNA_CONFIGURATION
#define  DNA_CONFIGURATION

typedef struct Task {
    char *host;
    char *port;
    char *message;
    int repeat_count;
    int thread_count;
} Task;

//typedef void (*ConfigurationServiceAgentInit) (
//        struct ConfigurationServiceAgent*,
//        char *producerHost,
//        char *consumerHost,
//        int producerPort,
//        int consumerPort,
//        char *producerEndpoint,
//        char *consumerEndpoint,
//        struct ResourceList*,
//        struct ResourceList*
//);

//struct ResourceList {
//    char *(*resources)[];
//    int length;
//};

struct Device {
    char *host;
    int port;
    char *endpoint;
};

struct ConfigurationServiceAgent {
    char *producerHost;
    char *consumerHost;
    int producerPort;
    int consumerPort;
//    char *producerEndpoint;
//    char *consumerEndpoint;
//    ResourceList *producerResources;
//    ResourceList *consumerResources;
//    ConfigurationServiceAgentInit init;
};

struct ConfigurationProducer {
    char *host;
    int port;
//    char **resources;
//    void (*init) (char *);
};

struct ConfigurationConsumer {
    char *host;
    int port;
//    char **resources;
//    void (*init) (char *);
};

struct ConfigurationQualityOfService {
    char *host;
    int port;
};

struct ResourceList {

};

typedef struct ConfigurationServiceAgent ConfigurationServiceAgent;
typedef struct ConfigurationProducer ConfigurationProducer;
typedef struct ConfigurationConsumer ConfigurationConsumer;
typedef struct ConfigurationQualityOfService ConfigurationQualityOfService;
typedef struct ResourceList ResourceList;
typedef struct Device Device;

//typedef struct ConfigurationQualityOfService {
//    Device *devices[];
//    int length;
////    char **resource;
////    void (*init) (char *);
//} ConfigurationQualityOfService;

#endif