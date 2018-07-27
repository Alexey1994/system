#include <windows.h>
#include <system/interfaces/file/file.h>
#include "PE.h"


function N_32 main ()
{
    Buffer code_buffer;
    Input  code_input;

    Buffer export_buffer;
    Input  export_input;

    PE     pe;
    Output pe_output;

    initialize_buffer(&code_buffer, 1024);
    write_in_buffer(&code_buffer, 0xC3);
    initialize_buffer_input(&code_buffer, &code_input);

    initialize_buffer(&export_buffer, 1024);
    write_in_buffer(&export_buffer, 0xC3);
    initialize_buffer_input(&export_buffer, &export_input);

    begin_PE(&pe);
    initialize_PE_export_section(&pe);
        add_section_in_PE(&pe, "Code", 2, 0x1000, 0x60000020, &code_input);
        //add_export_section_in_PE(&pe, "Export", 2, 0x2000, 0xC0300040, &export_input);

        begin_PE_export_section(&pe, 0x2000);
        end_PE_export_section(&pe);

        initialize_file_output(&pe_output, "out.exe");
        write_PE(&pe_output, &pe);
        deinitialize_output(&pe_output);

    deinitialize_PE_export_section(&pe);
    end_PE(&pe);

    return 0;
}
