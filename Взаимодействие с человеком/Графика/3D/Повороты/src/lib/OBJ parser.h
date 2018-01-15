#ifndef OBJ_PARSER_H_INCLUDED
#define OBJ_PARSER_H_INCLUDED

#include "lib/stream.h"


typedef struct
{
    float        *vertieces;
    unsigned int  length_vertieces;

    float        *normals;
    unsigned int  length_normals;

    unsigned int *indexes;
    unsigned int  length_indexes;
}
Object;


typedef struct
{/*
    float        *vertieces;
    unsigned int  length_vertieces;

    float        *normals;
    unsigned int  length_normals;

    unsigned int *indexes;
    unsigned int  length_indexes;*/
/*
    Array *vertieces;
    Array *normals;
    Array *indexes;*/
    Array *objects;
}
StaticModel;


StaticModel* parse_OBJ(Byte *stream_name,
                       Byte* (*open_stream)(Byte *stream_name),
                       void (*close_stream)(Byte *stream),
                       Byte (*get_byte)(Byte *stream),
                       Boolean end_of_file(Byte *stream));


#endif // OBJ_PARSER_H_INCLUDED
