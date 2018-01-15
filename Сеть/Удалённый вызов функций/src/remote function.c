private function Byte read_TCP_byte(Byte *connection)
{
    Byte byte;
    read_from_TCP(connection, &byte, 1);
    return byte;
}


private function Boolean is_end_remote_function_call(Byte *connection)
{
    return 0;
}


private procedure write_TCP_byte(Byte *connection, Byte byte)
{
    //printf("[%c %d]\n", byte, byte);
    write_in_TCP(connection, &byte, 1);
}


function Boolean parse_remote_array(Character *type, Output *output, Input *input)
{
    N_32 array_length = read_binary_N_32(input);
    N_32 i;
//printf("<parse ARRAY length %d>\n", array_length);
    Buffer *array_buffer;
    Output  array_buffer_output;

    Buffer array_elemet_buffer;

    for(i=0; i<array_length; ++i)
    {
        switch(*type)
        {
            case TYPE_N_8:
                //;N_8 t = read_binary_N_8(input);
                //printf("<parse N_8 %d>\n", t);
                //write_binary_N_8(output, t);
                write_binary_N_8(output, read_binary_N_8(input));
                break;

            case TYPE_N_16:
                write_binary_N_16(output, read_binary_N_16(input));
                break;

            case TYPE_N_32:
                write_binary_N_32(output, read_binary_N_32(input));
                break;

            case BEGIN_ARRAY:
                //printf("<parse inner ARRAY>\n");
                array_buffer = new(Buffer);
                initialize_buffer(array_buffer, 1);
                initialize_buffer_output(array_buffer, &array_buffer_output);

                parse_remote_array(type+1, &array_buffer_output, input);
                write_byte_array(output, &array_buffer, sizeof(Buffer*));
                break;
        }
    }

    return 1;

error:
    return 0;
}


function Byte* parse_remote_data(Character *type, Input *input)
{
    Buffer *array_buffer;
    Output  array_buffer_output;
    N_32    i;

    switch(*type)
    {
    case TYPE_N_8:
        return read_binary_N_8(input);

    case TYPE_N_16:
        return read_binary_N_16(input);

    case TYPE_N_32:
        return read_binary_N_32(input);

    case BEGIN_ARRAY:
        //printf("<parse ARRAY>\n");
        array_buffer = new(Buffer);
        initialize_buffer(array_buffer, 1);
        initialize_buffer_output(array_buffer, &array_buffer_output);
        parse_remote_array(type+1, &array_buffer_output, input);

        return array_buffer;
    }
}


procedure add_remote_data(Output *output, Array *structures_stack, N_32 type, N_32 data)
{
    N_32        *arguments_begin;
    DynamicData *top_data;
    Arr         *top_array;
    //Struct      *top_structure;
    DynamicData *new_data;
    Arr         *new_array;
    //Struct      *new_structure;

    if(structures_stack->length)
    {
        top_data = array_top(structures_stack);

        if(top_data->type == BEGIN_ARRAY)
        {
            top_array = top_data->data;

            if(!top_array->is_typed)
            {
                write_byte(&top_array->type_output, type);
                top_array->is_typed = 1;
            }
            else if(type != top_array->type.data[0])
                printf("error: types not equals(%d %d)\n", type, top_array->type.data[0]);
        }
    }

    switch(type)
    {
        case TYPE_N_8:
            write_binary_N_8(output, data);
            break;

        case TYPE_N_16:
            write_binary_N_16(output, data);
            break;

        case TYPE_N_32:
            write_binary_N_32(output, data);
            break;

        case BEGIN_ARRAY:
            write_binary_N_32(output, data);

            new_array = new(Arr);

            initialize_buffer(&new_array->type, 1);
            initialize_buffer_output(&new_array->type, &new_array->type_output);

            new_array->is_typed = 0;
            new_array->is_end = 0;

            new_data = create_dynamic_data(new_array, BEGIN_ARRAY);
            add_in_array(structures_stack, new_data);

            break;
/*
        case BEGIN_STRUCTURE:
            new_structure = new(Struct);

            initialize_buffer(&new_structure->type, 1);
            initialize_buffer_output(&new_structure->type, &new_structure->type_output);

            new_data = create_dynamic_data(new_structure, BEGIN_STRUCTURE);
            add_in_array(structures_stack, new_data);

            break;*/
    }
}


private function Boolean array_types_equals(Arr *parent_array, Arr *inner_array)
{
    N_32 i;

    if(parent_array->type.end_index != inner_array->type.end_index + 1)
        return 0;

    for(i=0; i<inner_array->type.end_index; ++i)
        if(parent_array->type.data[i+1] != inner_array->type.data[i])
            return 0;

    return 1;
}


procedure end_remote_array(Array *structures_stack)
{
    DynamicData *end_dynamic_data;
    Arr         *end_array;
    DynamicData *top_dynamic_data;
    Arr         *top_array;
    N_32         i;

    if(!structures_stack->length)
        goto not_array_error;

    end_dynamic_data = delete_from_array_top(structures_stack);

    if(end_dynamic_data->type != BEGIN_ARRAY)
        goto not_array_error;

    end_array = end_dynamic_data->data;

    if(!structures_stack->length)
        return;

    top_dynamic_data = array_top(structures_stack);

    if(top_dynamic_data->type != BEGIN_ARRAY)
        return;

    top_array = top_dynamic_data->data;

    if(!top_array->is_end)
    {
        for(i=0; i<end_array->type.end_index; ++i)
            write_byte(&top_array->type_output, end_array->type.data[i]);

        top_array->is_end = 1;
    }
    else
    {
        if(!array_types_equals(top_array, end_array))
            printf("error: array types not equals\n");
    }

    return;

not_array_error:
    printf("error: this is not array\n");
    return;
}

/*
procedure end_remote_structure(Call *call)
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
