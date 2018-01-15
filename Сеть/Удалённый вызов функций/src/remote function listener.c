typedef struct
{
    Character       *type;
    function Byte* (*remote_function)();
}
Remote_Function;


procedure begin_remote_return(Remote_Return *remote_return, Network_Source source)
{
    initialize_output(&remote_return->output, source, &write_TCP_byte);
    initialize_array(&remote_return->structures_stack, 2, 0);
}


procedure end_remote_return(Remote_Return *remote_return)
{
    deinitialize_array(&remote_return->structures_stack);
}


procedure add_remote_return_data(Remote_Return *remote_return, N_32 type, ...)
{
    N_32 *arguments_begin;

    arguments_begin = &type + 1;
    add_remote_data(&remote_return->output, &remote_return->structures_stack, type, *arguments_begin);
}


procedure end_remote_return_array(Remote_Return *remote_return)
{
    end_remote_array(&remote_return->structures_stack);
}


static procedure next_argument(Byte **type)
{
    while(**type && **type == BEGIN_ARRAY)
        ++(*type);

    if(**type)
        ++(*type);
}


private procedure remote_function_description_count(Byte *function_address, String *function_name, N_32 *count)
{
    ++*count;
}


private N_32 remote_functions_descriptions_count(Prefix_Tree *tree)
{
    N_32 count = 0;
    crawl_prefix_tree(tree, &remote_function_description_count, &count);
    return count;
}


private procedure remote_function_description(Remote_Function *remote_function, String *function_name, Remote_Return *remote_return)
{
    N_32    i;
    Byte   *type;
    String  type_string;

    type = remote_function->type;

    add_remote_return_data(remote_return, BEGIN_ARRAY, buffer_length(&function_name->buffer));
        for(i=function_name->buffer.begin_index; i<function_name->buffer.end_index; ++i)
            add_remote_return_data(remote_return, TYPE_N_8, function_name->buffer.data[i]);
    end_remote_return_array(remote_return);

    initialize_string(&type_string);
    write_null_terminated_byte_array(&type_string.output, "( ");

    while(*type)
    {
        switch(*type)
        {
            case TYPE_N_8:
                write_null_terminated_byte_array(&type_string.output, "N_8 ");
                break;

            case TYPE_N_16:
                write_null_terminated_byte_array(&type_string.output, "N_16 ");
                break;

            case TYPE_N_32:
                write_null_terminated_byte_array(&type_string.output, "N_32 ");
                break;

            case BEGIN_ARRAY:
                write_null_terminated_byte_array(&type_string.output, "[] ");
                break;
        }

        ++type;
    }

    write_null_terminated_byte_array(&type_string.output, ")");

    add_remote_return_data(remote_return, BEGIN_ARRAY, buffer_length(&type_string.buffer));
        for(i=type_string.buffer.begin_index; i<type_string.buffer.end_index; ++i)
            add_remote_return_data(remote_return, TYPE_N_8, type_string.buffer.data[i]);
    end_remote_return_array(remote_return);

    deinitialize_string(&type_string);
}


private procedure remote_functions_description(Remote_Function_Listener *listener, Remote_Return *remote_return)
{
    N_32 functions_length;

    functions_length = remote_functions_descriptions_count(listener->functions);

    add_remote_return_data(remote_return, BEGIN_ARRAY, functions_length*2);
        crawl_prefix_tree(listener->functions, &remote_function_description, remote_return);
    end_remote_return_array(remote_return);
}


private procedure on_remote_function_call(Network_Source source, Remote_Function_Listener *listener)
{
	String           function_name;
	Input            input;
	Byte            *type;
	Remote_Function *remote_function;
	Remote_Return    remote_return;

    initialize_input(&input, source, &read_TCP_byte, 0);
	initialize_string(&function_name);

    while(input_head(&input) != '\0')
    {
        write_byte(&function_name.output, input_head(&input));
        read_byte(&input);
    }

    write_byte(&function_name.output, '\0');

    if(!strcmp(function_name.buffer.data, "description"))
    {
        begin_remote_return(&remote_return, source);
            add_function_argument_32(&remote_return);
            remote_functions_description(listener, &remote_return);
        end_remote_return(&remote_return);

        return;
    }

    remote_function = find_in_prefix_tree(listener->functions, function_name.buffer.data);
    type = remote_function->type;

    procedure (*g)() = remote_function->remote_function;

    if(!g)
    {
        printf("function ");
        print_string(&function_name);
        printf("not found\n");
        return;
    }

    read_byte(&input);

    while(*type)
    {
        add_function_argument_32(parse_remote_data(type, &input));
        next_argument(&type);
    }

    begin_remote_return(&remote_return, source);
        add_function_argument_32(&remote_return);
        g();
    end_remote_return(&remote_return);
}


procedure begin_remote_functions(Remote_Function_Listener *listener)
{
    listener->functions = create_prefix_tree();
}


procedure add_remote_function(Remote_Function_Listener *listener, char *type, char *name, function Byte* (*function_pointer)())
{
    Remote_Function *remote_function;

    remote_function = new(Remote_Function);
    remote_function->remote_function = function_pointer;
    remote_function->type            = type;

    add_in_prefix_tree(listener->functions, name, remote_function);
}


procedure end_remote_functions(Remote_Function_Listener *listener)
{
    listener->TCP_connection = create_TCP_server("127.0.0.1", 8090, 1000, &on_remote_function_call, listener);
}
