#include <windows.h>
#include <system/interfaces/thread/thread.h>
#include "mouse.h"


N_32 main()
{
    //start_mouse_coords_update(1440, 900);

    for(;;)
    {
        //if(pressed_left_mouse_key())
            //printf("a");
        //printf("%c", get_pressed_key_code());

        printf("%d %d\n", get_mouse_coord_x(), get_mouse_coord_y());
        sleep_thread(10);
    }

    return 0;
}
