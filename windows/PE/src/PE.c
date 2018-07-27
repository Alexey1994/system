procedure begin_PE (PE *pe)
{
    N_32 i;

    initialize_buffer(&pe->sections, 1);
    initialize_buffer_output(&pe->sections, &pe->sections_output);

    for(i = 0; i < 16; ++i)
    {
        pe->data_directories[i].address = 0;
        pe->data_directories[i].size = 0;
    }
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

    if(size % 512)
        size = (size / 512 + 1) * 512;

    initialize_PE_section_name(section.name, name);
    section.address     = address;
    section.size        = size;
    section.access_bits = access_bits;
    section.input       = input;

    write_byte_array(&pe->sections_output, &section, sizeof(PE_Section));
}


procedure add_export_section_in_PE (PE *pe, Byte *name, N_32 size, N_32 address, N_32 access_bits, Input *input)
{
    /*PE_Section section;

    initialize_PE_section_name(section.name, name);
    section.address     = address;
    section.size        = size;
    section.access_bits = access_bits;
    section.input       = input;

    write_byte_array(&pe->sections_output, &section, sizeof(PE_Section));
*/
    pe->data_directories[0].address = address;
    pe->data_directories[0].size = size;
}


procedure initialize_PE_export_section(PE *pe)
{
    initialize_buffer(&pe->export_section.section, 10);
    initialize_buffer_output(&pe->export_section.section, &pe->export_section.section_output);
    initialize_buffer_input(&pe->export_section.section, &pe->export_section.section_input);
}


begin_PE_export_section(PE *pe, N_32 address)
{
    pe->export_section.address = address;

    pe->data_directories[0].address = address;
    pe->data_directories[0].size = 0;
}


end_PE_export_section(PE *pe)
{
    write_binary_N_32(&pe->export_section.section_output, 0);
    write_binary_N_32(&pe->export_section.section_output, 0);      //timestamp
    write_binary_N_32(&pe->export_section.section_output, 0);      //version
    write_binary_N_32(&pe->export_section.section_output, 0x2000 + 40); //name ASCIIZ address
    write_binary_N_32(&pe->export_section.section_output, 1);      //Начальный номер экспортируемых символов (больше или равен 1).
    write_binary_N_32(&pe->export_section.section_output, 2);      //Количество элементов в таблице адресов.
    write_binary_N_32(&pe->export_section.section_output, 2);      //Количество элементов в таблице имен и таблице номеров.
    write_binary_N_32(&pe->export_section.section_output, 0x2000 + 48); //RVA таблицы адресов.
    write_binary_N_32(&pe->export_section.section_output, 0x2000 + 56); //RVA таблицы имен.
    write_binary_N_32(&pe->export_section.section_output, 0x2080 + 64); //RVA таблицы номеров.
//0x2000 + 40
    write_null_terminated_byte_array(&pe->export_section.section_output, "Hi.exe");
    write_byte(&pe->export_section.section_output, '\0');
    write_byte(&pe->export_section.section_output, '\0');
//0x2000 + 48
    write_binary_N_32(&pe->export_section.section_output, 0x1000);      //адрес1
    write_binary_N_32(&pe->export_section.section_output, 0x1001);      //адрес2

    write_binary_N_32(&pe->export_section.section_output, 0x2000 + 68); //адрес имени1
    write_binary_N_32(&pe->export_section.section_output, 0x2000 + 80); //адрес имени2

    write_binary_N_16(&pe->export_section.section_output, 1);           //номер1
    write_binary_N_16(&pe->export_section.section_output, 2);           //номер2
//0x2000 + 68
    write_null_terminated_byte_array(&pe->export_section.section_output, "funtanische"); //имя1
    write_byte(&pe->export_section.section_output, '\0');
//0x2000 + 80
    write_null_terminated_byte_array(&pe->export_section.section_output, "tada");        //имя2
    write_byte(&pe->export_section.section_output, '\0');

    add_section_in_PE (pe, "Export", buffer_length(&pe->export_section.section), pe->export_section.address, 0xC0300040, &pe->export_section.section_input);
}


procedure deinitialize_PE_export_section(PE *pe)
{
    deinitialize_input(&pe->export_section.section_input);
    deinitialize_buffer(&pe->export_section.section);
}


private procedure write_PE_header (Output *output, PE *pe, N_32 number_of_sections)
{
    N_32 i;

    write_byte_array(output, "MZ", 2);

    for(i = 2; i < 0x3C; ++i)
        write_byte(output, 0);

    write_binary_N_32(output, 0x40);

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
        write_binary_N_32(output, pe->data_directories[i].address);
        write_binary_N_32(output, pe->data_directories[i].size);
    }
}


private function N_32 calculate_PE_image_size (PE *pe, N_32 number_of_sections)
{
    N_32        i;
    N_32        image_size;
    PE_Section *current_section;

    image_size = 0;

    for(i = 0; i < number_of_sections; ++i)
    {
        current_section = pe->sections.data + i * sizeof(PE_Section);

        if(current_section->address + current_section->size > image_size)
            image_size = current_section->address + current_section->size;
    }

    if(image_size % 4096)
        image_size = (image_size / 4096 + 1) * 4096;

    return image_size;
}


private procedure write_optional_PE_header (Output *output, PE *pe, N_32 number_of_sections)
{
    write_binary_N_16(output, APPLICATION_32);
    write_binary_N_16(output, 6);

    write_binary_N_32(output, 0);                           //size of code
    write_binary_N_32(output, 0);                           //size of initialized data
    write_binary_N_32(output, 0);                           //size of uninitialized data
    write_binary_N_32(output, 0x00001000);                  //address of entry point
    write_binary_N_32(output, 0x00001000);                  //base of code
    write_binary_N_32(output, 0x00000000);                  //base of data
    write_binary_N_32(output, 0x00010000);                  //image base

    write_binary_N_32(output, 4096);                        //section alignment
    write_binary_N_32(output, 512);                         //file alignment

    write_binary_N_32(output, 0x04);                        //OS version
    write_binary_N_32(output, 0);                           //Image version
    write_binary_N_32(output, 0x04);                        //Subsystem version
    write_binary_N_32(output, 0);

    write_binary_N_32(output, calculate_PE_image_size(pe, number_of_sections)); //size of image
    write_binary_N_32(output, 0x00001000);                  //size of headers

    write_binary_N_32(output, 0);                           //checksum
    write_binary_N_16(output, 3);                           //subsystem(console)
    write_binary_N_16(output, 0);

    write_binary_N_32(output, 0x00001000);                  //stack reserve
    write_binary_N_32(output, 0x00001000);                  //stack commit

    write_binary_N_32(output, 0x00002000);                  //heap reserve
    write_binary_N_32(output, 0x00002000);                  //heap commit

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
    N_32        size_of_headers;
    N_32        end_of_headers;
    N_32        section_position;
    PE_Section *current_section;
    N_32        data_position;

    number_of_sections = buffer_length(&pe->sections) / sizeof(PE_Section);
    size_of_headers = 312 + number_of_sections * 40;

    if(size_of_headers % 512)
        end_of_headers = (size_of_headers / 512 + 1) * 512;
    else
        end_of_headers = size_of_headers / 512 * 512;

    write_PE_header(output, pe, number_of_sections);
    write_optional_PE_header(output, pe, number_of_sections);
    write_PE_data_directories_header(output, pe);

    data_position = 312;
    section_position = end_of_headers;

    for(i = 0; i < number_of_sections; ++i)
    {
        current_section = pe->sections.data + i * sizeof(PE_Section);
        write_PE_section_header(output, current_section, section_position);
        data_position += 40;

        if(current_section->size % 512)
            section_position += (current_section->size / 512 + 1) * 512;
        else
            section_position += current_section->size / 512 * 512;
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
