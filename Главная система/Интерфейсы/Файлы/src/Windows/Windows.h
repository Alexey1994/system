#define GENERIC_READ  0x80000000
#define GENERIC_WRITE 0x40000000

#define CREATE_NEW        1
#define CREATE_ALWAYS     2
#define OPEN_EXISTING     3
#define OPEN_ALWAYS       4
#define TRUNCATE_EXISTING 5

#define FILE_ATTRIBUTE_NORMAL 128


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


typedef struct
{
    Boolean       is_end_of_file;
    Windows_File *file_source;
}
File;


private import stdcall function Windows_File* OpenFile    (Character *path, Windows_File *file, N_32 flags);
private import stdcall function Boolean       ReadFile    (Byte *file, Byte *buffer, N_32 buffer_length, N_32 *bytes_readed, Byte *overlapped);
private import stdcall function Boolean       CloseHandle (Byte *handle);


private import stdcall function Windows_File* CreateFileA(
    Byte         *name,
    N_32          flags1, //режим доступа
    N_32          flags2, //разрешить другим процессам доступ к файлу, 0 - запретить всё
    void         *security_attributes, // 0 если не наследуется дочерними процессами
    N_32          flags4, //CREATE_NEW | CREATE_ALWAYS | OPEN_EXISTING | OPEN_ALWAYS | TRUNCATE_EXISTING
    N_32          flags5,
    Windows_File *file
);

private import stdcall function Boolean WriteFile(
    Windows_File *file,
    Byte         *data,
    N_32          data_length,
    N_32         *bytes_writed,
    Byte         *overlapped
);


#include "Windows.c"
