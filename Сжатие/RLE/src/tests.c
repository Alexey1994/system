#include <stdio.h>
#include "RLE.h"


void put_byte(FILE *file, Byte data)
{
    fputc(data, file);
}


int main()
{
    FILE   *input_file        = fopen("in.txt", "rb");
    Stream *input_stream      = create_stream(input_file, fgetc, feof);
    FILE   *compressed_file   = fopen("compress.txt", "wb");
    Stream *compress_stream   = create_output_stream(compressed_file, put_byte);
    FILE   *decompress_file   = fopen("decompress.txt", "wb");
    Stream *decompress_stream = create_output_stream(decompress_file, put_byte);

    compress_RLE(input_stream, compress_stream, 2);

    fclose(compressed_file);
    destroy_stream(compress_stream);

    compressed_file=fopen("compress.txt", "rb");
    compress_stream=create_stream(compressed_file, fgetc, feof);

    decompress_RLE(compress_stream, decompress_stream, 2);

    return 0;
}
