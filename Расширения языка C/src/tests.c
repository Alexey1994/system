//#define BIG_ENDIAN
#include "extends.h"


function Z_32 main()
{
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

    return 0;
}
