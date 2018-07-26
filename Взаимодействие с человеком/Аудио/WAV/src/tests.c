#include <windows.h>
#include <system/devices/sound/sound.h>
#include <system/interfaces/files/files.h>
#include "WAV.h"


export function N_32 main ()
{
    WAV    wav;
    Input  input;

    initialize_file_input(&input, "a.wav");
    read_WAV(&wav, &input);

    play_sound(&input);

    //for(;;);

    return 0;
}

