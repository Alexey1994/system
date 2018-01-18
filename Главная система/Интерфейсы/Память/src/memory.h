#ifndef MEMORY_H_INCLUDED
#define MEMORY_H_INCLUDED


function  Byte* allocate_memory (N_32 size);
procedure       free_memory     (Byte *memory_address);


#include "memory.c"

#endif // MEMORY_H_INCLUDED
