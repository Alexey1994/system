#include <windows.h>
#include "TCP.h"


function N_32 main()
{
	Byte *connection;
	Byte  buffer[512];

    connection = create_TCP("vk.com", 80);

    if(connection == 0)
        printf("error\n");

	snprintf(buffer, 512,
        "GET / HTTP 1.1\r\n"
        "Connection: close\r\n\r\n");

	write_in_TCP(connection, buffer, strlen(buffer));
	read_from_TCP(connection, buffer, 512);

	printf(buffer);

    return 0;
}
