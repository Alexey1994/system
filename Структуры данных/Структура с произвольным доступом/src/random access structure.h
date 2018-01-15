#ifndef RANDOM_ACCESS_STRUCTURE_H_INCLUDED
#define RANDOM_ACCESS_STRUCTURE_H_INCLUDED


#include <extends/extends.h>


typedef struct
{
    Byte *structure;

    function Byte* (*get_element)(struct Random_Access_Structure *structure, N_32 position);
    function N_32  (*get_length)(struct Random_Access_Structure *structure);
}
Random_Access_Structure;


function Random_Access_Structure* create_random_access_structure (
	Byte *structure,
	function Byte* (*get_element)(Random_Access_Structure *structure, N_32 position),
	function N_32  (*get_length)(Random_Access_Structure *structure)
);

procedure destroy_random_access_structure (Random_Access_Structure *structure);

procedure initialize_random_access_structure (
	Random_Access_Structure *random_access_structure,
	Byte *structure,
	function Byte* (*get_element)(Random_Access_Structure *structure, N_32 position),
	function N_32  (*get_length)(Random_Access_Structure *structure)
);

procedure deinitialize_random_access_structure(Random_Access_Structure *structure);


#include "random access structure.c"

#endif // RANDOM_ACCESS_STRUCTURE_H_INCLUDED
