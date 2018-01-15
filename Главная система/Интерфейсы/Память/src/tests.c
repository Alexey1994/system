//#include <windows.h>
#include <x86 32 bit.h>
#include "memory.h"


N_32 main()
{
    Byte *memory_address;

    memory_address = allocate_memory(32);
    free_memory(memory_address);

    return 0;
}
