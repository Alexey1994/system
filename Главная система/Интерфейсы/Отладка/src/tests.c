//#include <windows.h>
#include <x86 32 bit.h>
#include <system/devices/keyboard/keyboard.h>
#include "debug.h"


procedure print_finded_PCI_device(PCI_Device *device)
{
    Output log;

    initialize_debug_output(&log);
    print_PCI_device(&log, device);
}


typedef struct
{
    Byte blue;
    Byte green;
    Byte red;
}
Pixel;


N_32 main()
{
    
    /*write_null_terminated_byte_array(&log, "Hi, Alexey. sdjhfgjksdhjkg hsjkdgh jksd kghsdjk  hgjkshdjgk sdjkghjkdsj hfjkshdjkfh jskdjfs hdjk fhsjkfh j");

    for(;;)
    {
        if(pressed_key('Q'))
            write_null_terminated_byte_array(&log, " :)");
    }*/

    find_PCI_devices(&print_finded_PCI_device);

    N_32  *video_address = 0x7E00 + 0x28;
    Pixel *screen        = *video_address;

    N_32 i;

    for(i=0; i<640 * 480; ++i)
        screen[i].red = i;

    return 0;
}
