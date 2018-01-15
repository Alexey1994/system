function String* create_string ()
{
    String *string;

    string = new(String);
    initialize_string(string);

    return string;
}


procedure destroy_string (String *string)
{
    deinitialize_string(string);
    free_memory(string);
}


procedure initialize_string (String *string)
{
    initialize_buffer(&string->buffer, 2);
    initialize_buffer_output(&string->buffer, &string->output);
}


procedure deinitialize_string (String *string)
{
    deinitialize_buffer(&string->buffer);
}


function Z_32 compare_strings (String *a, String *b)
{
    N_32 i;
    N_32 j;
    Z_32 distance;

    for(i=a->buffer.begin_index, j=b->buffer.begin_index; i<a->buffer.end_index && j<b->buffer.end_index; ++i, ++j)
    {
        distance = b->buffer.data[j] - a->buffer.data[i];

        if(distance)
            return distance;
    }

    return (b->buffer.end_index - b->buffer.begin_index) - (a->buffer.end_index - a->buffer.begin_index);
}


procedure print_string (String *string)
{
    N_32 i;

    for(i=string->buffer.begin_index; i<string->buffer.end_index; ++i)
        printf("%c", string->buffer.data[i]);
}
