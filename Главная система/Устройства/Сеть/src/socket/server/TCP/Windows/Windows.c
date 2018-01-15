typedef struct
{
    TCP_Server        *server;
    function  Byte*  (*run_on_request)(TCP_Connection *connection, Byte *arguments);
    Byte              *request_arguments;
}
Server_Update_arguments;


static procedure update_TCP_server(Server_Update_arguments *arguments)
{
    TCP_Server        *server                                                       = arguments->server;
    function Byte*   (*run_on_request)(TCP_Connection *connection, Byte *arguments) = arguments->run_on_request;
    Byte              *request_arguments                                            = arguments->request_arguments;
    free(arguments);

    Boolean is_non_blocking_mode;

    for(;;)
    {
        TCP_Connection *connection;

        connection = new(TCP_Connection);

        connection->socket = accept(server->connection.socket, 0, 0);

        if(connection->socket < 0)
        {
            sleep_thread(1);
            continue;
        }

        is_non_blocking_mode = 1;
        ioctlsocket(connection->socket, NON_BLOCKING_MODE, &is_non_blocking_mode);

        run_on_request(connection, request_arguments);
        closesocket(connection->socket);
    }
}


procedure initialize_TCP_server(
    TCP_Server      *server,
    Byte            *host,
    N_16             port,
    N_32             maximum_connections,
    function Byte* (*run_on_request)(TCP_Connection *connection, Byte *arguments),
    Byte            *request_arguments
)
{
    Windows_Socket_Address_Info  sock_addr;
    Host_Data                   *host_data;
    Server_Update_arguments     *arguments;

    if(!initialize_Windows_sockets())
        goto error;

    host_data = gethostbyname(host);

    if(!host_data)
        goto error;

    sock_addr.family     = IPv4;
    sock_addr.port       = htons(port);
    sock_addr.in_address = *((N_32*)host_data->address_list[0]);

    server->connection.socket = socket(IPv4, SOCKET_STREAM, TCP_PROTOCOL);

    if(server->connection.socket == -1)
    {
        //print_error("socket error\n");
        goto error;
    }

    if(bind(server->connection.socket, &sock_addr, sizeof(Windows_Socket_Address_Info)) == -1)
    {
        //print_error("bind error\n");
        goto error;
    }

    if(listen(server->connection.socket, maximum_connections))
    {
        //print_error("listen error\n");
        goto error;
    }

    arguments = new(Server_Update_arguments);

    arguments->server            = server;
    arguments->run_on_request    = run_on_request;
    arguments->request_arguments = request_arguments;

    run_thread(update_TCP_server, arguments);

    return server;

error:
    printf("TCP server error\n");
    return 0;
}


void deinitialize_server(TCP_Server *server)
{

}
