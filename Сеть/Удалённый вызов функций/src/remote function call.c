procedure begin_remote_call(Call *call, Byte *function_name, Character *return_type)
{
    call->return_type = return_type;
    call->connection = create_TCP("127.0.0.1", 8090);
    initialize_output(&call->output, call->connection, &write_TCP_byte);

    write_null_terminated_byte_array(&call->output, function_name);
    write_byte(&call->output, '\0');
    initialize_array(&call->structures_stack, 2, 0);
}


function Byte* end_remote_call(Call *call)
{
    Byte   *return_data;
    Input   return_input;

    initialize_input(&return_input, call->connection, &read_TCP_byte, &is_end_remote_function_call);
    return_data = parse_remote_data(call->return_type, &return_input);

    destroy_TCP(call->connection);

    return return_data;
}


procedure add_call_data(Call *call, N_32 type, ...)
{
    N_32 *arguments_begin;

    arguments_begin = &type + 1;
    add_remote_data(&call->output, &call->structures_stack, type, *arguments_begin);
}


procedure end_call_array(Call *call)
{
    end_remote_array(&call->structures_stack);
}

/*
procedure end_call_structure(Call *call)
{
    DynamicData *end_dynamic_data;
    Arr         *end_structure;
    N_32         i;

    if(!call->structures_stack.length)
        goto not_structure_error;

    end_dynamic_data = delete_from_array_top(&call->structures_stack);

    if(end_dynamic_data->type != BEGIN_STRUCTURE)
        goto not_structure_error;

    end_structure = end_dynamic_data->data;

    return;

not_structure_error:
    printf("error: this is not structure\n");
    return;
}
*/
