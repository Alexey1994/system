#include "../../connection.h"


private import stdcall function  N_32  send (Z_32 connection, Byte *data, N_32 length_data, N_32 flags);
private import stdcall function  N_32  recv (Z_32 connection, Byte *data, N_32 length_data, N_32 flags);


#include "Windows.c"
