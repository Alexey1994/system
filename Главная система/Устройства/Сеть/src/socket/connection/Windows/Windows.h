#include <data structures/buffer/buffer.h>


typedef struct
{
    Z_32     socket;
    Buffer   input_buffer;
    Buffer   output_buffer;
    Boolean  output_locked;
    Byte    *output_listener_ID;
}
TCP_Connection;


#include "Windows.c"
