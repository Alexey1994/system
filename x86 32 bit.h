#define __x86_32_bit__


unsigned int main();


void start_system()
{
    main();

    for(;;);
}


#include <extends/extends.h>
