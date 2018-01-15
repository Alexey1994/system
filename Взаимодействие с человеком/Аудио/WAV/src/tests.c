//#include <stdio.h>
#include <windows.h>
#include <system/devices/sound/sound.h>
#include "WAV.h"


typedef struct _iobuf
{
	char*	_ptr;
	int	_cnt;
	char*	_base;
	int	_flag;
	int	_file;
	int	_charbuf;
	int	_bufsiz;
	char*	_tmpfname;
} FILE;


Byte    fgetc (FILE *file);
Boolean feof  (FILE *file);


int main()
{
    WAV wav;
    Input  input;
    FILE  *f;

    f = fopen("a.wav", "rb");
    initialize_input(&input, f, &fgetc, &feof);
    read_WAV(&wav, &input);

    play_sound(&input);

    for(;;);

    return 0;
}

