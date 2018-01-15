private function Byte read_file_byte(File *file)
{
    Byte byte;
    N_32 bytes_readed;

    ReadFile(file->file_source, &byte, 1, &bytes_readed, 0);

    if(!bytes_readed)
        file->is_end_of_file = 1;

    return byte;
}


private function Boolean end_of_file(File *file)
{
    return file->is_end_of_file;
}


private procedure destroy_file(File *file)
{
    CloseHandle(file->file_source);
    free(file);
}


function Boolean initialize_file_input (Input *file_input, Character *path)
{
    Windows_File  file;
    File         *file_source;

    file_source = new(File);
    file_source->file_source = OpenFile(path, &file, 0);

    if(file.error_code)
        goto error;

    file_source->is_end_of_file = 0;
    initialize_input(file_input, file_source, &read_file_byte, &end_of_file);
    file_input->destroy_source = &destroy_file;

    return 1;

error:
    free(file_source);
    return 0;
}
