#include <stdio.h>
#include "buffer.h"


function int main()
{
    Buffer buffer;
    Output buffer_output;

    initialize_buffer(&buffer, 2);
    initialize_buffer_output(&buffer, &buffer_output);

    write_N_32(&buffer_output, 12345);
    write_byte(&buffer_output, '\0');

    printf(buffer.data);

    return 0;
}
