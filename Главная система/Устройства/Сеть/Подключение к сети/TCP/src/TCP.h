#ifndef TCP_NETWORK_CONNECTION
#define TCP_NETWORK_CONNECTION


function  Byte*    create_TCP    (Byte *host, N_16 port);
procedure          destroy_TCP   (Byte *connection);

procedure          write_in_TCP  (Byte *connection, Byte *data, N_32 length_data);
procedure          read_from_TCP (Byte *connection, Byte *data, N_32 length_data);


#include "TCP.c"

#endif //TCP_NETWORK_CONNECTION
