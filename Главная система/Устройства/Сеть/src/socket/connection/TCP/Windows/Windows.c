function Boolean initialize_TCP_connection (TCP_Connection *connection, Byte *host, N_16 port)
{
    Windows_Socket_Address_Info  address_info;
    Host_Data                   *host_data;
    Boolean                      is_non_blocking_mode;

    if(!initialize_Windows_sockets())
        goto error;

    host_data = gethostbyname(host);

    if(!host_data)
        goto error;

    address_info.family      = IPv4;
    address_info.in_address  = *((N_32*)host_data->address_list[0]);
    address_info.port        = htons(port);

    if(address_info.in_address == -1)
        goto error;

    connection->socket = socket(IPv4, SOCKET_STREAM, TCP_PROTOCOL);

    if(connection->socket == -1)
        goto error;

    is_non_blocking_mode = 1;
    printf("ioctlsocket status %d\n", ioctlsocket(connection->socket, NON_BLOCKING_MODE, &is_non_blocking_mode));

    while(!connect(connection->socket, &address_info, sizeof(Windows_Socket_Address_Info)))
    {//printf("error socket\n");
        //closesocket(connection->socket);
        //goto error;
    }

    return 1;

error:
    return 0;
}


procedure deinitialize_TCP_connection (TCP_Connection *connection)
{
    closesocket(connection->socket);
}


procedure write_in_TCP_connection (TCP_Connection *connection, Byte *data, N_32 length_data)
{
	send(connection->socket, data, length_data, 0);
}


procedure read_from_TCP_connection (TCP_Connection *connection, Byte *data, N_32 length_data)
{
	recv(connection->socket, data, length_data, 0);
}


private function Byte read_byte_from_TCP_Connection(TCP_Connection *connection)
{
    Byte byte;
    Z_32 data_length;

    if(!buffer_length(&connection->input_buffer))
    {
        while(connection->output_buffer.end_index);

        loop
        {
            data_length = recv(connection->socket, connection->input_buffer.data, 4096, 0);

            if(data_length > 0)
                break;

            //printf("lock input\n");
            sleep_thread(1);
        }

        //printf("get %d bytes\n", data_length);

        connection->input_buffer.end_index = data_length;
        connection->input_buffer.begin_index = 0;
    }

    return read_from_buffer(&connection->input_buffer);
}


private function Boolean is_end_of_TCP_Connection_data(TCP_Connection *connection)
{
    return 0;
}


private function write_byte_in_TCP_Connection(TCP_Connection *connection, Byte byte)
{
    while(buffer_length(&connection->input_buffer) || buffer_length(&connection->output_buffer) == connection->output_buffer.reserve || connection->output_locked)
    {
        //printf("lock output [%d, %d, %d]\n", buffer_length(&connection->input_buffer), buffer_length(&connection->output_buffer) == connection->output_buffer.reserve, connection->output_locked);
    }

    write_in_buffer(&connection->output_buffer, byte);
}


private procedure listen_TCP_Connection_output(TCP_Connection *connection)
{
    loop
    {
        if(connection->output_buffer.end_index)
        {
            send(connection->socket, connection->output_buffer.data, connection->output_buffer.reserve, 0);
            //printf("send\n");
            connection->output_buffer.end_index = 0;
        }

        connection->output_locked = 0;
        sleep_thread(1);
        connection->output_locked = 1;
        sleep_thread(1);
    }
}


procedure initialize_TCP_Connection_input_output(TCP_Connection *connection, Input *input, Output *output)
{
    initialize_buffer(&connection->input_buffer, 4096);
    initialize_input(input, connection, &read_byte_from_TCP_Connection, &is_end_of_TCP_Connection_data);

    initialize_buffer(&connection->output_buffer, 4096);
    initialize_output(output, connection, &write_byte_in_TCP_Connection);

    connection->output_listener_ID = run_thread(&listen_TCP_Connection_output, connection);
}
