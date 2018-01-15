#include <windows.h>
#include "system library.h"


N_32 main()
{
    procedure (*f)();
    Byte       *args[1];

    f = open_system_function("msvcrt.dll", "printf");

    if(!f)
    {
        printf("function %s not found in %s\n", "printf", "msvcrt.dll");
        return 0;
    }

    args[0] = "Hi";
    run_system_function(f, args, 1);

    return 0;
}
