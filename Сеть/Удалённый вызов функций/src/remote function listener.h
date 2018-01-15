#ifndef REMOTE_FUNCTION_LISTENER_H_INCLUDED
#define REMOTE_FUNCTION_LISTENER_H_INCLUDED


#include <system/devices/network/server/TCP/TCP.h>
#include <system/interfaces/system library/system library.h>
#include <data structures/string/string.h>
#include <data structures/prefix tree/prefix tree.h>
#include "remote function.h"


typedef struct
{
    Byte        *TCP_connection;
    Prefix_Tree *functions;
}
Remote_Function_Listener;


#include "remote function listener.c"

#endif //REMOTE_FUNCTION_LISTENER_H_INCLUDED
