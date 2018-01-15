#include "arithmetic.h"


int real_signum(float x)
{
    if(x == 0)
        return 0;

    if(x>0)
        return 1;
    else
        return -1;
}


int integer_signum(int x)
{
    if(!x)
        return 0;

    if(x>0)
        return 1;
    else
        return -1;
}
