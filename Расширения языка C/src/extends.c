#ifdef __x86_32_bit__
# include "x86 32 bit/x86 32 bit.h"
#endif


procedure copy_memory (Byte *data1, Byte *data2, N_32 length)
{
    N_32 i;

    for(i=0; i<length; ++i)
        data1[i] = data2[i];
}


procedure initialize_dynamic_data (Dynamic_Data *dynamic_data, Byte *data, Byte type)
{
    dynamic_data->data = data;
    dynamic_data->type = type;
}


procedure revert_bytes_order (Byte *array, N_32 length)
{
    N_32 i;
    Byte tmp;

    for(i = 0; i < length/2; ++i)
    {
        tmp = array[i];
        array[i] = array[length-i-1];
        array[length-i-1] = tmp;
    }
}


procedure swap (Byte *element_1, Byte *element_2, N_32 length)
{
    Byte saved_value;
    N_32 i;

    for(i=0; i<length; ++i)
    {
        saved_value  = element_1[i];
        element_1[i] = element_2[i];
        element_2[i] = saved_value;
    }
}