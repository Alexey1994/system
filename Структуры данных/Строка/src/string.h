#ifndef STRING_H_INCLUDED
#define STRING_H_INCLUDED


#include <extends/extends.h>
#include <data structures/buffer/buffer.h>


typedef struct
{
	Buffer buffer;
	Output output;
}
String;


function  String* create_string       ();
procedure         destroy_string      (String *string);
procedure         initialize_string   (String *string);
procedure         deinitialize_string (String *string);

function  Z_32    compare_strings     (String *a, String *b);
procedure         print_string        (String *string);


//#include <libs/input/input.h>
//#include <libs/output/output.h>

/*
typedef struct
{
	Byte *data;
	N_32  reserve;
	N_32  begin_index;
	N_32  end_index;
}
Buffer;


function  Buffer* create_buffer            (N_32 reserve);
procedure         destroy_buffer           (Buffer *buffer);
procedure         initialize_buffer        (Buffer *buffer, N_32 reserve);
procedure         deinitialize_buffer      (Buffer *buffer);

function  Input*  create_buffer_input      (Buffer *buffer);
procedure         initialize_buffer_input  (Buffer *buffer, Input *input);

function  Output* create_buffer_output     (Buffer *buffer);
procedure         initialize_buffer_output (Buffer *buffer, Output *output);
*/

#include "string.c"

#endif // STRING_H_INCLUDED
