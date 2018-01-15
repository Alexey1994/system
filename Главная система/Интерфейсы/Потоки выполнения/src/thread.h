#ifndef THREAD_H_INCLUDED
#define THREAD_H_INCLUDED


function  Byte* run_thread   (procedure (*thread_function)(), Byte *arg);
procedure       sleep_thread (N_32 milliseconds);


#include "thread.c"

#endif // THREAD_H_INCLUDED
