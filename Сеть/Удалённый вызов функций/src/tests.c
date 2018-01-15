#include <windows.h>
#include "remote function call.h"
#include "remote function listener.h"

#include "test application manager.c"

/*
procedure fun(N_32 x, N_32 y)
{
    Call call;

    begin_call(&call, "fun");
        add_element(&call, TYPE_N_32, x);
        add_element(&call, TYPE_N_32, y);
    end_call(&call);
}


function N_32 main()
{
    listen_remote_function();
    for(;;);

    fun(10, 20);

    return 0;
}
*/
