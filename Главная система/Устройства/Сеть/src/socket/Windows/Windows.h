#define IPv4                      2
#define SOCKET_STREAM             1
#define TCP_PROTOCOL              6

#define SHUTDOWN_RECEIVE_AND_SEND 2
#define NON_BLOCKING_MODE         0x8004667e


typedef struct
{
    Z_16 family;
    N_16 port;
    N_32 in_address;
    Byte zero[8];
}
Windows_Socket_Address_Info;

typedef struct
{
    Byte  *host_name;
    Byte **aliases;
    N_16   address_type;
    N_16   length;
    Byte **address_list;
}
Host_Data;


private import stdcall function  Host_Data* gethostbyname (Byte *host);
private import stdcall function  N_16       htons         (N_16 port);
private import stdcall function  Z_32       socket        (N_32 family, N_32 type, N_32 protocol);
private import stdcall function  N_32       closesocket   (Z_32 socket);
private import stdcall function  N_32       connect       (Z_32 conection, Windows_Socket_Address_Info *address_info, N_32 size_of_address_info);
private import stdcall function  N_32       ioctlsocket   (Z_32 socket, N_32 command, Byte *arguments);


#include "Windows.c"