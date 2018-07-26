//#define BIG_ENDIAN
#include <x86 32 bit.h>
#include "extends.h"

#include <system/interfaces/debug/debug.h>

Output debug_output;


procedure print_finded_PCI_device(PCI_Device *device)
{
    N_32 BAR_0;
    N_32 BAR_1;
    N_32 BAR_2;
    N_32 BAR_3;
    N_32 BAR_4;
    N_32 BAR_5;

    N_32 BAR_0_memory;

    print_PCI_device(&debug_output, device);
    write_byte(&debug_output, '\n');

    BAR_0 = read_from_PCI_device_config(device, 0x10);
    BAR_1 = read_from_PCI_device_config(device, 0x14);
    BAR_2 = read_from_PCI_device_config(device, 0x18);
    BAR_3 = read_from_PCI_device_config(device, 0x1C);
    BAR_4 = read_from_PCI_device_config(device, 0x20);
    BAR_5 = read_from_PCI_device_config(device, 0x24);
/*
    if(BAR_0 & 0b1)
    {
        write_null_terminated_byte_array(&debug_output, "memory i/o ");
        write_hex_N_32(&debug_output, (~(BAR_0 & 0b11111111111111111111111111110000)) + 1 );
    }
    else
        write_null_terminated_byte_array(&debug_output, "in out i/o");

    write_byte(&debug_output, ' ');
    
    if(BAR_1 & 0b1)
        write_null_terminated_byte_array(&debug_output, "in out i/o");
    else
    {
        write_null_terminated_byte_array(&debug_output, "memory i/o ");
        write_hex_N_32(&debug_output, (~(BAR_1 & 0b11111111111111111111111111110000)) + 1 );
    }
*/

/*
    if(BAR_2 & 0b1)
        write_null_terminated_byte_array(&debug_output, "in out i/o");
    else
    {
        write_null_terminated_byte_array(&debug_output, "memory i/o ");
        write_hex_N_32(&debug_output, (~(BAR_2 & 0b11111111111111111111111111110000)) + 1 );
    }

    if(BAR_3 & 0b1)
        write_null_terminated_byte_array(&debug_output, "in out i/o");
    else
    {
        write_null_terminated_byte_array(&debug_output, "memory i/o ");
        write_hex_N_32(&debug_output, (~(BAR_3 & 0b11111111111111111111111111110000)) + 1 );
    }
*/

/*
    if(BAR_4 & 0b1)
        write_null_terminated_byte_array(&debug_output, "in out i/o");
    else
    {
        write_null_terminated_byte_array(&debug_output, "memory i/o ");
        write_hex_N_32(&debug_output, (~(BAR_4 & 0b11111111111111111111111111110000)) + 1 );
    }

    if(BAR_5 & 0b1)
        write_null_terminated_byte_array(&debug_output, "in out i/o");
    else
    {
        write_null_terminated_byte_array(&debug_output, "memory i/o ");
        write_hex_N_32(&debug_output, (~(BAR_5 & 0b11111111111111111111111111110000)) + 1 );
    }
*/

    //write_N_32(&debug_output, read_from_PCI_device(device, 4));
    //write_byte(&debug_output, '\n');
    //write_byte(&debug_output, '\n');
}


procedure find_PCI_express_devices ()//(procedure (*on_finded)(PCI_Device *device))
{
    N_32 *data;
    N_32  signature;
    Byte *signature_data;
    N_32  i;

    signature_data = &signature;
    signature_data[0] = 'M';
    signature_data[1] = 'C';
    signature_data[2] = 'F';
    signature_data[3] = 'G';

    data = 0;
    //signature = *((N_32*)"MCFG");
    //revert_bytes_order(&signature, 4);

    for(i=1; i; ++i)
    {
        data = i;

        if(*data == signature)
        {
            write_null_terminated_byte_array(&debug_output, "PCI express address: ");
            write_hex_N_32(&debug_output, i);
            write_null_terminated_byte_array(&debug_output, ", MCFG length: ");
            write_N_32(&debug_output, data[1]);
            write_byte(&debug_output, '\n');
        }

        //write_N_32(&debug_output, i);
        //write_byte(&debug_output, '\n');
    }
}


function N_32 main()
{
    /*
    Dynamic_Data variable;
    N_32         i;

    initialize_dynamic_data(&variable, 123, 1);

    for(i=0; i<4; ++i)
        printf("%d ", ((Byte*)&variable.data)[i]);

    printf("\n");

    convert_big_to_little_endian(&variable.data, 4);

    for(i=0; i<4; ++i)
        printf("%d ", ((Byte*)&variable.data)[i]);

    printf("\n");

    convert_little_to_big_endian(&variable.data, 4);

    for(i=0; i<4; ++i)
        printf("%d ", ((Byte*)&variable.data)[i]);

    printf("\n");
*/


    Byte *t = 0xB8000;
    N_32 i;

    for(i=0; i<80*25; ++i)
        t[i*2] = 0;

    initialize_debug_output(&debug_output);

    //find_PCI_express_devices();
    find_PCI_devices(&print_finded_PCI_device);
    //find_PCI_devices(&print_finded_PCI_device);


/*
    Byte *video = 0x00000010;
    N_32 i;

    for(i=0; i<100; ++i)
        video[i] = i;
*/
/*
    Byte *VESA_info = 0x7E00;
    N_16 *video_modes = VESA_info + 0xe;

    initialize_debug_output(&debug_output);

    for(; *video_modes != 0xffff; ++video_modes)
    {
        write_hex_N_16(&debug_output, *video_modes);
        write_byte(&debug_output, ' ');
    }
*/
    return 0;
}
