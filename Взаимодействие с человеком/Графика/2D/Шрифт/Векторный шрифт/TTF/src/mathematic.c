#include "mathematic.h"


N power(N a, N power)
{
    N value = 1;

    for(; power; --power)
        value *= a;

    return value;
}


R real_power(R a, N power)
{
    R value = 1;

    for(; power; --power)
        value *= a;

    return value;
}
