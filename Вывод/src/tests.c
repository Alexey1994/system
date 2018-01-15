#include <stdio.h>
#include "output.h"


procedure write_byte_in_file(FILE *file, Byte byte)
{
    fputc(byte, file);
}


function int main()
{
    FILE   *output_file;
    Output  output;

    output_file = fopen("output.txt", "wb");
    initialize_output (&output, output_file, write_byte_in_file);

    write_N_32(&output, 146);

    return 0;
}
