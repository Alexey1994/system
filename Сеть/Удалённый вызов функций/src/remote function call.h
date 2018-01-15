#ifndef REMOTE_FUNCTION_CALL_H_INCLUDED
#define REMOTE_FUNCTION_CALL_H_INCLUDED


#include <system/devices/network/connection/TCP/TCP.h>
#include <data structures/buffer/buffer.h>
#include "remote function.h"


typedef struct
{
	Byte   *connection;
	Output  output;
	Input   input;
	Array   arguments;
}
Remote_Function_Call;


typedef struct
{
    Byte      *connection;
    Buffer     out_buffer;
    Output     output;

    Array      structures_stack;
    Character *return_type;
}
Call;


function  Boolean initialize_remote_function_call   (Remote_Function_Call *call, Byte *host, N_16 port);
procedure         deinitialize_remote_function_call (Remote_Function_Call *call);

procedure begin_call(Call *call, Byte *function_name, Character *return_type);
function  Byte* end_call(Call *call);

procedure add_argument(Call *call, N_32 type, ...);

procedure add_structure_element(Call *call, N_32 type, ...);
procedure end_structure(Call *call);

procedure add_array_element(Call *call, N_32 type, ...);
procedure end_array(Call *call);

function          remote_function_call         (Remote_Function_Call *call, Byte *function_name, ...);


#include "remote function call.c"

#endif // REMOTE_FUNCTION_CALL_H_INCLUDED
