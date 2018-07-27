#ifndef PE_H_INCLUDED
#define PE_H_INCLUDED


#include <windows.h>
#include <input/input.h>
#include <output/output.h>
#include <data structures/buffer/buffer.h>


typedef enum
{
    I386_MACHINE = 0x014C
}
Machine;

typedef enum
{
    APPLICATION_32 = 0x010B
}
PE_Type;


typedef struct
{
    Machine machine;

    struct
    {
        N_32 address;
        N_32 size;
    }
    data_directories[16];

    struct
    {
        N_32   address;
        Buffer section;
        Output section_output;
        Input  section_input;
    }
    export_section;

    Buffer  sections;
    Output  sections_output;
}
PE;


typedef struct
{
    Byte name[8];
    N_32 address;
    N_32 access_bits;
    N_32 size;
    Input *input;
}
PE_Section;


procedure begin_PE (PE *pe);
    procedure add_section_in_PE (PE *pe, Byte *name, N_32 size, N_32 address, N_32 access_bits, Input *input);
    procedure write_PE          (Output *output, PE *pe);
procedure end_PE (PE *pe);


#include "PE.c"

#endif //PE_H_INCLUDED
