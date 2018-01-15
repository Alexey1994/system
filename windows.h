#ifndef WINDOWS_H_INCLUDED
#define WINDOWS_H_INCLUDED


#define __WIN32__

#include <extends/extends.h>


#define import   __attribute__((dllimport))
#define export   __attribute__((dllexport))
#define stdcall  __attribute__((__stdcall__))
#define cdecl    __attribute__((__cdecl__))


#endif // WINDOWS_H_INCLUDED
