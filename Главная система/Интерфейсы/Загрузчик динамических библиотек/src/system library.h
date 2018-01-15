#ifndef SYSTEM_LIBRARY_H_INCLUDED
#define SYSTEM_LIBRARY_H_INCLUDED


#include <extends/extends.h>


function  Byte* open_system_function (Byte *library_name, Byte *function_name);
//function  Byte* run_system_function  (function Byte* (*f)(), Byte **args, Z_32 length);


#include "system library.c"

#endif // SYSTEM_LIBRARY_H_INCLUDED
