#ifndef RLE_H_INCLUDED
#define RLE_H_INCLUDED


#include <libs/stream/stream.h>


void compress_RLE   (Stream *input_stream, Stream *output_stream, int chunk_size);
void decompress_RLE (Stream *input_stream, Stream *output_stream, int chunk_size);


#include "RLE.c"

#endif // RLE_H_INCLUDED
