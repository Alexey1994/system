#ifndef TCP_NETWORK_CONNECTION
#define TCP_NETWORK_CONNECTION


#include "../connection.h"
#include <input/input.h>
#include <output/output.h>


function Boolean initialize_TCP_Connection_input_output(Byte *host, N_16 port, Input *input, Output *output);


#include "TCP.c"

#endif //TCP_NETWORK_CONNECTION
