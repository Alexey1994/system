#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED


#include <extends/extends.h>


typedef struct
{
    Byte      **data;
    N_32        length;
    N_32        buffer_length;
    N_32        reserve;
    procedure (*destroy_node)(char *node);
}
Array;


procedure                          initialize_array        (Array *array, N_32 reserve, procedure (*destroy_node)(Byte *node));
procedure                          deinitialize_array      (Array *array);

procedure                          clear_array             (Array *array);

procedure                          add_in_array            (Array *array, Byte *data);
function  Byte*                    delete_from_array_top   (Array *array);
function  Byte*                    array_top               (Array *array);
function  Byte*                    array_data              (Array *array, N_32 index);
procedure                          crawl_array             (Array *array, procedure (*crawl_func)(Byte *node));


#include "array.c"

#endif // ARRAY_H_INCLUDED
