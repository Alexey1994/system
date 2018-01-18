#ifndef TCP_NETWORK_SERVER_H_INCLUDED
#define TCP_NETWORK_SERVER_H_INCLUDED


#include <system/interfaces/thread/thread.h>


typedef int Network_Source;


typedef struct
{
    Network_Source      source;
    Byte               *address;
    //struct sockaddr_in  sock_addr;
}
Server;


Server* create_TCP_server(
    Byte           *host,
    unsigned short  port,
    N_32            maximum_connections,
    int           (*run_on_request)(Input *input, Output *output, Byte *arguments),
    Byte           *request_arguments
);


void destroy_server(Server *server);


#include "TCP.c"

#endif //TCP_NETWORK_SERVER_H_INCLUDED
