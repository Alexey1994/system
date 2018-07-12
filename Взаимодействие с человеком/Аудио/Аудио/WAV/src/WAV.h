#ifndef WAVE_H_INCLUDED
#define WAVE_H_INCLUDED


#include <extends/extends.h>
#include <input/input.h>


typedef struct
{
    N_32 data_size;
}
WAV;


Byte* read_WAV(WAV *wav, Input *input);


#include "WAV.c"

#endif // WAVE_H_INCLUDED
