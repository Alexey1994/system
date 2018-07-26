#include <windows.h>

#define GENERIC_READ  0x80000000
#define GENERIC_WRITE 0x40000000

#define CREATE_NEW        1
#define CREATE_ALWAYS     2
#define OPEN_EXISTING     3
#define OPEN_ALWAYS       4
#define TRUNCATE_EXISTING 5

#define FILE_ATTRIBUTE_NORMAL 128

typedef N_32 File;

import stdcall function File CreateFileA(
    Byte *name,
    N_32 flags1, //режим доступа
    N_32 flags2, //разрешить другим процессам доступ к файлу, 0 - запретить всё
    void *security_attributes, // 0 если не наследуется дочерними процессами
    N_32 flags4, //CREATE_NEW | CREATE_ALWAYS | OPEN_EXISTING | OPEN_ALWAYS | TRUNCATE_EXISTING
    N_32 flags5,
    File file
);

import stdcall function Boolean ReadFile(
    File file,
    Byte *buffer,
    N_32 buffer_size,
    N_32 *bytes_read,
    void *overlapped
);

//flags1 - режим доступа
//flags2 - разрешить другим процессам доступ к файлу, 0 - запретить всё

function N_32 main ()
{
    File file;
    Byte buffer[65536];
    N_32 bytes_readed;
    N_32 i;

    file = CreateFileA("\\\\.\\E:", GENERIC_READ | GENERIC_WRITE, 0, 0, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, 0);
    ReadFile(file, buffer, 65536, &bytes_readed, 0);

    //printf("%d", bytes_readed);

    for(i = 0; i < 65536; ++i)
        printf("%d ", buffer[i]);

    return 0;
}

