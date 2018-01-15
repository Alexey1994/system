#ifndef GRAPHICS_PROGRAM_SPACE_H_INCLUDED
#define GRAPHICS_PROGRAM_SPACE_H_INCLUDED


#include <libs/extends/extends.h>
#include <libs/data structures/array/array.h>


typedef struct
{
    Byte       *element;
    procedure (*refresh_element)(Byte *element);
    procedure (*destroy_element)(Byte *element);
}
Program_Space_Element;


function Program_Space_Element* create_program_space_element (
	Byte       *element,
	procedure (*refresh_element)(Byte *element),
	procedure (*destroy_element)(Byte *element)
);

procedure destroy_program_space_element(Program_Space_Element *element);


typedef struct
{
	N_32   x;
	N_32   y;
	N_32   width;
	N_32   height;
    Array *elements;
}
Program_Space;


function  Program_Space* create_program_space         (N_32 x, N_32 y, N_32 width, N_32 height);
procedure                destroy_program_space        (Program_Space *program_space);
procedure                add_element_in_program_space (Program_Space *program_space, Program_Space_Element *element);
procedure                refresh_program_space        (Program_Space *program_space);


#include "program space.c"

#endif // GRAPHICS_PROGRAM_SPACE_H_INCLUDED
