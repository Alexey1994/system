private import stdcall function Byte* LoadLibraryA   (N_16 *file_name);
private import stdcall function Byte* GetProcAddress (Byte *library, N_16 *procedure_name);

#include "Windows.c"
