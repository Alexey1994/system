procedure begin_PE (PE *pe)
{
    initialize_buffer(&pe->sections, 1);
    initialize_buffer_output(&pe->sections, &pe->sections_output);
}


private procedure initialize_PE_section_name (Byte *section_name, Byte *name)
{
    N_32 i;

    for(i = 0; i < 8; ++i)
    {
        section_name[i] = *name;

        if(*name)
            ++name;
    }
}


procedure add_section_in_PE (PE *pe, Byte *name, N_32 size, N_32 address, N_32 access_bits, Input *input)
{
    PE_Section section;

    initialize_PE_section_name(section.name, name);
    section.address     = address;
    section.size        = size;
    section.access_bits = access_bits;
    section.input       = input;

    write_byte_array(&pe->sections_output, &section, sizeof(PE_Section));
}


private procedure write_PE_header (Output *output, PE *pe, N_32 number_of_sections)
{
    N_32 i;

    write_byte_array(output, "MZ", 2);

    for(i = 2; i < 0x3C; ++i)
        write_byte(output, 0);

    write_binary_N_32(output, 0x80);

    for(i = 0; i < 0x40; ++i)
        write_byte(output, 0);

    write_byte_array(output, "PE\0\0", 4);
    write_binary_N_16(output, I386_MACHINE);
    write_binary_N_16(output, number_of_sections);

    write_binary_N_32(output, 0);
    write_binary_N_32(output, 0);
    write_binary_N_32(output, 0);

    write_binary_N_16(output, 0xE0);
    write_binary_N_16(output, 0x030F); //charachteristics(flags)
}


private procedure write_PE_data_directories_header (Output *output, PE *pe)
{
    N_32 i;

    write_binary_N_32(output, 16);

    for(i = 0; i < 16; ++i)
    {
        write_binary_N_32(output, 0);
        write_binary_N_32(output, 0);
    }
}


private procedure write_optional_PE_header (Output *output, PE *pe)
{
    write_binary_N_16(output, APPLICATION_32);
    write_binary_N_16(output, 6);

    write_binary_N_32(output, 0);          //size of code
    write_binary_N_32(output, 0);          //size of initialized data
    write_binary_N_32(output, 0);          //size of uninitialized data
    write_binary_N_32(output, 0x00001000); //address of entry point
    write_binary_N_32(output, 0x00001000); //base of code
    write_binary_N_32(output, 0x00000000); //base of data
    write_binary_N_32(output, 0x00010000); //image base

    write_binary_N_32(output, 4096);       //section alignment
    write_binary_N_32(output, 512);        //file alignment

    write_binary_N_32(output, 0x04);       //OS version
    write_binary_N_32(output, 0);          //Image version
    write_binary_N_32(output, 0x04);       //Subsystem version
    write_binary_N_32(output, 0);

    write_binary_N_32(output, 0x00002000); //size of image
    write_binary_N_32(output, 0x00001000); //size of headers

    write_binary_N_32(output, 0);          //checksum
    write_binary_N_16(output, 3);          //subsystem(console)
    write_binary_N_16(output, 0);

    write_binary_N_32(output, 0x00001000); //stack reserve
    write_binary_N_32(output, 0x00001000); //stack commit

    write_binary_N_32(output, 0x00002000); //heap reserve
    write_binary_N_32(output, 0x00002000); //heap commit

    write_binary_N_32(output, 0);
}


private procedure write_PE_section_header (Output *output, PE_Section *section, N_32 section_position)
{
    write_byte_array(output, section->name, 8);
    write_binary_N_32(output, section->size);
    write_binary_N_32(output, section->address);
    write_binary_N_32(output, section->size);

    write_binary_N_32(output, section_position);
    write_binary_N_32(output, 0);
    write_binary_N_32(output, 0);
    write_binary_N_32(output, 0);
    write_binary_N_32(output, section->access_bits);
}


procedure write_PE (Output *output, PE *pe)
{
    N_32        i;
    N_32        number_of_sections;
    PE_Section *current_section;
    N_32        data_position;

    number_of_sections = buffer_length(&pe->sections) / sizeof(PE_Section);
    
    write_PE_header(output, pe, number_of_sections);
    write_optional_PE_header(output, pe);
    write_PE_data_directories_header(output, pe);

    data_position = 376;

    for(i = 0; i < number_of_sections; ++i)
    {
        current_section = pe->sections.data + i * sizeof(PE_Section);
        write_PE_section_header(output, current_section, 0x200);
        data_position += 40;
    }

    while(data_position % 512)
    {
        write_byte(output, 0);
        ++data_position;
    }

    for(i = 0; i < number_of_sections; ++i)
    {
        current_section = pe->sections.data + i * sizeof(PE_Section);

        while(!end_of_input(current_section->input))
        {
            write_byte(output, read_byte(current_section->input));
            ++data_position;
        }

        while(data_position % 512)
        {
            write_byte(output, 0);
            ++data_position;
        }
    }
}

procedure end_PE (PE *pe)
{
    deinitialize_buffer(&pe->sections);
}
