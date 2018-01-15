//#include <windows.h>
#include <x86 32 bit.h>
#include "keyboard.h"


N_32 main()
{
    /*start_mouse_coords_update(1440, 900);

    for(;;)
    {
        if(key_up('Q'))
            printf("up\n");

        if(key_down('Q'))
            printf("down\n");

        //if(pressed_left_mouse_key())
            //printf("a");
        //printf("%c", get_pressed_key_code());

        //printf("%f %f\n", mouse_coord_x, mouse_coord_y);
        Sleep(10);
    }*/

    Byte *t = 0xb8000;

    *t = '1';

    while(!pressed_key('Q'));

    *t = '2';

    return 0;
}
