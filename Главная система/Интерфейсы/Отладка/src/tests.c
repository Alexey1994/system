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


N_32 main()
{
    
    /*write_null_terminated_byte_array(&log, "Hi, Alexey. sdjhfgjksdhjkg hsjkdgh jksd kghsdjk  hgjkshdjgk sdjkghjkdsj hfjkshdjkfh jskdjfs hdjk fhsjkfh j");

    for(;;)
    {
        if(pressed_key('Q'))
            write_null_terminated_byte_array(&log, " :)");
    }*/

    find_PCI_devices(&print_finded_PCI_device);

    return 0;
}
