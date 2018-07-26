#include <windows.h>
#include <system/interfaces/file/file.h>
#include "PE.h"


function N_32 main ()
{
    Buffer code_buffer;
    Input  code_input;
    PE     pe;
    Output pe_output;

    initialize_buffer(&code_buffer, 1024);

    write_in_buffer(&code_buffer, 0xC3);

    initialize_buffer_input(&code_buffer, &code_input);

    begin_PE(&pe);
        add_section_in_PE(&pe, "Code", 512, 0x1000, 0x60000020, &code_input);

        initialize_file_output(&pe_output, "out.exe");
        write_PE(&pe_output, &pe);
        deinitialize_output(&pe_output);
    end_PE(&pe);

    return 0;
}
