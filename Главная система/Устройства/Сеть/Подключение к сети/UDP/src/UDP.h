#ifndef UDP_NETWORK_CONNECTION
#define UDP_NETWORK_CONNECTION


function  Byte* create_UDP    (Byte *host, N_16 port);
procedure       destroy_UDP   (Byte *connection);

procedure       write_in_UDP  (Byte *connection, Byte *data, N_32 length_data);
procedure       read_from_UDP (Byte *connection, Byte *data, N_32 length_data);


#include "UDP.c"

#endif //UDP_NETWORK_CONNECTION