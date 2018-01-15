#include <stdio.h>
#include "error.h"


int main()
{
    set_error_function(printf);
    print_error("Ok\n");

    return 0;
}
