#ifndef TCP_NETWORK_SERVER_H_INCLUDED
#define TCP_NETWORK_SERVER_H_INCLUDED


#include "../server.h"
#include <system/interfaces/thread/thread.h>
#include "../../connection/TCP/TCP.h"


typedef struct
{
    TCP_Connection      connection;
    Byte               *address;
    //struct sockaddr_in  sock_addr;
}
TCP_Server;


procedure initialize_TCP_server(
    TCP_Server      *server,
    Byte            *host,
    N_16             port,
    N_32             maximum_connections,
    function Byte* (*run_on_request)(TCP_Connection *connection, Byte *arguments),
    Byte            *request_arguments
);


procedure deinitialize_server(TCP_Server *server);


#include "TCP.c"

#endif //TCP_NETWORK_SERVER_H_INCLUDED
