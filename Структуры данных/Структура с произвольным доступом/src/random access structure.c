#include "random access structure.h"


function Random_Access_Structure* create_random_access_structure (
	Byte *structure,
	function Byte* (*get_element)(Random_Access_Structure *structure, N_32 position),
	function N_32  (*get_length)(Random_Access_Structure *structure)
)
{
    Random_Access_Structure *random_access_structure;

    random_access_structure = new(Random_Access_Structure);
    initialize_random_access_structure(random_access_structure, structure, get_element, get_length);

    return random_access_structure;
}


procedure destroy_random_access_structure (Random_Access_Structure *structure)
{
	deinitialize_random_access_structure(structure);
    free_memory(structure);
}


procedure initialize_random_access_structure (
	Random_Access_Structure *random_access_structure,
	Byte *structure,
	function Byte* (*get_element)(Random_Access_Structure *structure, N_32 position),
	function N_32  (*get_length)(Random_Access_Structure *structure)
)
{
	random_access_structure->structure   = structure;
    random_access_structure->get_element = get_element;
    random_access_structure->get_length  = get_length;
}


procedure deinitialize_random_access_structure(Random_Access_Structure *structure)
{

}