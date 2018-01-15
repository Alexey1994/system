Windows_Sockets TCP_Sockets = {0};


function Byte* create_TCP (Byte *host, N_16 port)
{
    Windows_Socket_Address_Info  address_info;
    Host_Data                   *host_data;
    Z_32                         connection_socket;

    if(!TCP_Sockets.version)
        WSAStartup(0x0202, &TCP_Sockets);

    host_data = gethostbyname(host);

    if(!host_data)
        goto error;

    address_info.family      = IPv4;
    address_info.in_address  = *((N_32*)host_data->address_list[0]);
    address_info.port        = htons(port);

    if(address_info.in_address == -1)
        goto error;

    connection_socket = socket(IPv4, SOCKET_STREAM, TCP_PROTOCOL);

    if(connection_socket == -1)
        goto error;

    if(connect(connection_socket, &address_info, sizeof(Windows_Socket_Address_Info)))
    {
        closesocket(connection_socket);
        goto error;
    }

    return connection_socket;

error:
    return 0;
}


void destroy_TCP (Byte *connection)
{
    closesocket(connection);
}


void write_in_TCP (Byte *connection, Byte *data, N_32 length_data)
{
	send(connection, data, length_data, 0);
}


void read_from_TCP (Byte *connection, Byte *data, N_32 length_data)
{
	recv(connection, data, length_data, 0);
}
