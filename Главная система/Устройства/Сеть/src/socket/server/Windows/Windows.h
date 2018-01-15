private import stdcall function  Z_32  accept    (Z_32 socket, Windows_Socket_Address_Info *address, N_32 address_length);
private import stdcall function  Z_32  bind      (Z_32 socket, Windows_Socket_Address_Info *address, N_32 address_length);
private import stdcall function  Z_32  listen    (Z_32 socket, N_32 maximum_connections);


#include "Windows.c"