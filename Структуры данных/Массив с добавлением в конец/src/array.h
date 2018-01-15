#ifndef ARRAY_H_INCLUDED
#define ARRAY_H_INCLUDED


#include <extends/extends.h>
#include <data structures/random access structure/random access structure.h>


typedef struct
{
    Byte      **data;
    N_32        length;
    N_32        buffer_length;
    N_32        reserve;
    procedure (*destroy_node)(char *node);
}
Array;


function  Array*                   create_array            (N_32 reserve, procedure (*destroy_node)(Byte *node));
procedure                          destroy_array           (Array *array);

procedure                          initialize_array        (Array *array, N_32 reserve, procedure (*destroy_node)(Byte *node));
procedure                          deinitialize_array      (Array *array);

procedure                          add_in_array            (Array *array, Byte *data);
function  Byte*                    delete_from_array_top   (Array *array);
function  Byte*                    array_top               (Array *array);
function  Byte*                    array_data              (Array *array, N_32 index);
procedure                          crawl_array             (Array *array, procedure (*crawl_func)(Byte *node));

function  Random_Access_Structure* create_array_structure  (Array *array);
procedure                          destroy_array_structure (Random_Access_Structure *structure);


#include "array.c"

#endif // ARRAY_H_INCLUDED
