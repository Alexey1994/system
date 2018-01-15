#ifndef OBJ_PARSER_H_INCLUDED
#define OBJ_PARSER_H_INCLUDED


#include <input/input.h>
#include <mathematic/geometry/point/point.h>


typedef struct
{
    R_32 *vertieces;
    N_32  vertieces_length;

    R_32 *normals;
    N_32  normals_length;

    R_32 *texture_coords;
    N_32  texture_coords_length;

    Array polygons;
}
Object;


typedef struct
{
    Array objects;
}
StaticModel;


function  Boolean parse_OBJ(StaticModel *model, Input *input, procedure (*initialize_input)(Input *input, Byte *path));


#include "OBJ parser.c"

#endif // OBJ_PARSER_H_INCLUDED
