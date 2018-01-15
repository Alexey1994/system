#define IPv4                      2
#define SOCKET_STREAM             1
#define TCP_PROTOCOL              6

#define SHUTDOWN_RECEIVE_AND_SEND 2

typedef struct
{
    N_16  version;
    N_16  high_version;
    Byte  description[257];
    Byte  system_status[129];
    N_32  maximum_sockets;
    N_32  maximum_UDP_size;
    Byte *vendor_info;
}
Windows_Sockets;

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


private import stdcall function  N_32       WSAStartup    (N_16 version, Windows_Sockets *sockets);
private import stdcall function  Host_Data* gethostbyname (Byte *host);
private import stdcall function  N_16       htons         (N_16 port);
private import stdcall function  Z_32       socket        (N_32 family, N_32 type, N_32 protocol);
private import stdcall function  N_32       closesocket   (Z_32 socket);
private import stdcall function  N_32       connect       (Z_32 conection, Windows_Socket_Address_Info *address_info, N_32 size_of_address_info);
private import stdcall function  N_32       send          (Z_32 connection, Byte *data, N_32 length_data, N_32 flags);
private import stdcall function  N_32       recv          (Z_32 connection, Byte *data, N_32 length_data, N_32 flags);


#include "Windows.c"
