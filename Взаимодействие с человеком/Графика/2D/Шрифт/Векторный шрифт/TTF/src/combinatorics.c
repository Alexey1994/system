#include "combinatorics.h"


N factorial(N n)
{
    N value = 1;

    for(; n; --n)
        value *= n;

    return value;
}


N C(N n, N k)
{
    return factorial(n)/( factorial(k) * factorial(n-k) );
}
