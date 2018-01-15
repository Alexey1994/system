typedef struct
{
    Server *server;
    int   (*run_on_request)(Network_Source source, Byte *arguments);
    Byte   *request_arguments;
}
Server_Update_arguments;


Windows_Sockets TCP_server_sockets = {0};


static void update_TCP_server(Server_Update_arguments *arguments)
{
    Server *server                                                  = arguments->server;
    int   (*run_on_request)(Network_Source source, Byte *arguments) = arguments->run_on_request;
    Byte   *request_arguments                                       = arguments->request_arguments;
    free(arguments);

    for(;;)
    {
        Network_Source client = accept(server->source, 0, 0);

        if(client < 0)
        {
            //sleep_thread(1);
            continue;
        }

        run_on_request(client, request_arguments);
        //shutdown(client, SHUTDOWN_RECEIVE_AND_SEND);
        closesocket(client);
    }
}


Server* create_TCP_server(
    Byte           *host,
    unsigned short  port,
    N_32            maximum_connections,
    int           (*run_on_request)(Network_Source source, Byte *arguments),
    Byte           *request_arguments
)
{
    Windows_Socket_Address_Info  sock_addr;
    Host_Data                   *host_data;
    Server                      *server;
    Server_Update_arguments     *arguments;

    if(!TCP_server_sockets.version)
        WSAStartup(0x0202, &TCP_server_sockets);

    //memset(&sock_addr, 0, sizeof(Windows_Socket_Address_Info));

    host_data = gethostbyname(host);

    if(!host_data)
        goto error;

    sock_addr.family     = IPv4;
    sock_addr.port       = htons(port);
    sock_addr.in_address = *((N_32*)host_data->address_list[0]);

    server = new(Server);

    server->source = socket(IPv4, SOCKET_STREAM, TCP_PROTOCOL);

    if(server->source == -1)
    {
        //print_error("socket error\n");
        goto error;
    }

    if(bind(server->source, &sock_addr, sizeof(Windows_Socket_Address_Info)) == -1)
    {
        //print_error("bind error\n");
        goto error;
    }

    if(listen(server->source, maximum_connections))
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


void destroy_server(Server *server)
{

}
