#define SOUND_BUFFER_LENGTH 8820

#define CALLBACK_THREAD     0x20000
#define CALLBACK_FUNCTION   0x30000
#define CALLBACK_EVENT      0x50000
#define WHDR_BEGINLOOP      4
#define MM_WOM_DONE         0x3BD


typedef struct
{
    N_16 format;
    N_16 number_of_channels;
    N_32 samples_per_seconds;
    N_32 bytes_per_seconds;
    N_16 block_align;
    N_16 bits_per_sample;
    N_16 size_of_appended_information;
}
Windows_Sound_Format;

typedef struct Windows_Sound_Buffer
{
    Byte                        *data;
    N_32                         buffer_length;
    N_32                         bytes_recorded;
    Byte                        *user;
    N_32                         flags;
    N_32                         loops;
    struct Windows_Sound_Buffer *next;
    Byte                        *reserved;
}
Windows_Sound_Buffer;


typedef struct
{
    Input                *input;
    Windows_Sound_Buffer  sound_buffer;
    Byte                  buffer1_data[SOUND_BUFFER_LENGTH];
    Byte                  buffer2_data[SOUND_BUFFER_LENGTH];
    Windows_Sound_Buffer  buffer1;
    Windows_Sound_Buffer  buffer2;
    N_32                  current_buffer_index;
    Boolean               read_data;
}
Sound_Data;


import stdcall function  N_32 waveOutOpen(
    Byte                 *sound_device,
    N_32                  device_ID,
    Windows_Sound_Format *format,
    procedure           (*on_buffer_end)(Byte *sound_device, Byte *message, Byte *arguments, Byte *parameter1, Byte *parameter2),
    Byte                 *arguments,
    N_32                  flags
);

import stdcall function  N_32 waveOutPrepareHeader(
    Byte                 *sound_device,
    Windows_Sound_Buffer *buffer,
    N_32                  size_of_struct_buffer
);

import stdcall function  N_32 waveOutWrite(
    Byte                 *sound_device,
    Windows_Sound_Buffer *buffer,
    N_32                  size_of_struct_buffer
);


#include "Windows.c"
