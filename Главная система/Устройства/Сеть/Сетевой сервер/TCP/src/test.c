#include <windows.h>
#include "TCP.h"
//#include <system/devices/network/connection/TCP/TCP.h>


procedure listen_server(Byte *connection)
{
    Byte byte;

    printf("connected\n");
/*
    read_from_TCP(connection, &byte, 1);
    printf("%c", byte);

    read_from_TCP(connection, &byte, 1);
    printf("%c", byte);

    read_from_TCP(connection, &byte, 1);
    printf("%c", byte);

    read_from_TCP(connection, &byte, 1);
    printf("%c", byte);*/
}


function N_32 main()
{
    create_TCP_server("127.0.0.1", 80, 10000, &listen_server, 0);

    for(;;);

	return 0;
}
