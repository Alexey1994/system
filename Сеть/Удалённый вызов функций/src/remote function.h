#ifndef REMOTE_FUNCTION_H_INCLUDED
#define REMOTE_FUNCTION_H_INCLUDED


#include <data structures/array/array.h>
#include <input/input.h>
#include <output/output.h>


typedef enum
{
    BEGIN_FUNCTION  = '(',
    END_FUNCTION    = ')',

    BEGIN_STRUCTURE = '{',
    END_STRUCTURE   = '}',

    BEGIN_ARRAY     = '[',
    END_ARRAY       = ']',

    TYPE_N_8        = '1',
    TYPE_N_16       = '2',
    TYPE_N_32       = '3'
}
Remote_Function_Types;


typedef struct
{
    Buffer type;
    Output type_output;

    Buffer  output_buffer;
    Output  output;

    Boolean is_typed;
    Boolean is_end;
}
Arr;


typedef struct
{
    Buffer type;
    Output type_output;

    Buffer  output_buffer;
    Output  output;

    Boolean is_typed;
    Boolean is_end;

    Array structure;
}
Struct;


typedef struct
{
    Array  structures_stack;
    Output output;
}
Remote_Return;


#include "remote function.c"

#endif //REMOTE_FUNCTION_H_INCLUDED
