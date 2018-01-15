typedef struct
{
    Boolean  is_end_of_file;
    Byte    *file_source;
}
File;


typedef struct
{
	N_8     size_struct;
	Boolean file_on_hard_disk;
	N_16    error_code;
	N_16    reserved1;
	N_16    reserved2;
	Byte    path_name[256];
}
Windows_File;


private import stdcall function Byte*   OpenFile    (Character *path, Windows_File *file, N_32 flags);
private import stdcall function Boolean ReadFile    (Byte *file, Byte *buffer, N_32 buffer_length, N_32 *bytes_readed, Byte *overlapped);
private import stdcall function Boolean CloseHandle (Byte *handle);


#include "Windows.c"
