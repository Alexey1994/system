#include <windows.h>
//#include "network.h"
#include "socket/server/TCP/TCP.h"


procedure listen_server(TCP_Connection *connection)
{
    Byte buffer[128];

    printf("connected\n\n");

    Input  input;
    Output output;
/*
    initialize_TCP_Connection_input_output(connection, &input, &output);

    for(;;)
    {
        //read_from_TCP_connection(connection, buffer, 128);
        printf("server receive\n", buffer);

        loop
        {
            Byte character = read_byte(&input);

            if(!character)
                break;

            printf("%c", character);
        }

        clear_buffer(&connection->input_buffer);

        printf("\n\n");

        printf("server transmission\n");
        //write_in_TCP_connection(connection, "Hi!", 4);

        write_null_terminated_byte_array(&output, "Hi!");
        write_byte(&output, 0);
    }*/
}


N_32 main()
{
    /*Byte host[16];

    get_IPv4_host_address(host);
    printf(host);*/

    TCP_Connection connection;
    TCP_Server     server;
    Input          input;
    Output         output;

    initialize_TCP_server(&server, "127.0.0.1", 80, 10000, &listen_server, 0);
    initialize_TCP_connection(&connection, "127.0.0.1", 80);
    initialize_TCP_Connection_input_output("127.0.0.1", 80, &input, &output);

    for(;;)
    {
        Byte buffer[128];

        printf("client transmission\n");
        write_null_terminated_byte_array(&output, "Hi");
        write_byte(&output, 0);
        //write_in_TCP_connection(&connection, "Hi", 3);

        //read_from_TCP_connection(&connection, buffer, 128);
        printf("client receive\n", buffer);

        loop
        {
            Byte character = read_byte(&input);

            if(!character)
                break;

            printf("%c", character);
        }

        clear_buffer(&connection.input_buffer);

        //sleep_thread(1000);
        printf("\n");
    }

    loop{}

    return 0;
}
