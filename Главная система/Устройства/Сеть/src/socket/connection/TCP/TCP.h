#ifndef TCP_NETWORK_CONNECTION
#define TCP_NETWORK_CONNECTION


#include "../connection.h"
#include <input/input.h>


typedef struct
{
    Z_32     socket;
    Buffer   input_buffer;
    Buffer   output_buffer;
    Boolean  output_locked;
    Byte    *output_listener_ID;
}
TCP_Connection;


function  Boolean initialize_TCP_connection    (TCP_Connection *connection, Byte *host, N_16 port);
procedure         deinitialize_TCP_connection  (TCP_Connection *connection);

procedure         write_in_TCP_connection      (TCP_Connection *connection, Byte *data, N_32 length_data);
procedure         read_from_TCP_connection     (TCP_Connection *connection, Byte *data, N_32 length_data);


#include "TCP.c"

#endif //TCP_NETWORK_CONNECTION
