#include <windows.h>
#include "network info.h"


N_32 main()
{
    Byte host[16];

    get_IPv4_host_address(host);
    printf(host);

    return 0;
}
