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


Windows_Sockets windows_sockets = {0};


private import stdcall function  N_32  WSAStartup (N_16 version, Windows_Sockets *sockets);
private import stdcall procedure       WSACleanup ();


#include "Windows.c"
