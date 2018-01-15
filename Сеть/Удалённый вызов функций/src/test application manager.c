#include <system/interfaces/files/files.h>


Array applications_source;


Array* applications(char *search_string)
{
    Call call;

    begin_remote_call(&call, "applications", "[[1");
        add_call_data(&call, BEGIN_ARRAY, strlen(search_string));
            for(; *search_string; ++search_string)
                add_call_data(&call, TYPE_N_8, *search_string);
        end_call_array(&call);
    return end_remote_call(&call);
}


Array* description()
{
    Call call;

    begin_remote_call(&call, "description", "[[1");
    return end_remote_call(&call);
}


function Boolean string_contains(String *string, Buffer *search_string)
{
    N_32    i;
    N_32    j;
    Byte    current_character;
    Boolean is_contains;

    for(i=string->buffer.begin_index; i<string->buffer.end_index; ++i)
    {
        is_contains = 1;

        for(j=search_string->begin_index; j < search_string->end_index; ++j)
        {
            if(i + j >= string->buffer.end_index)
            {
                is_contains = 0;
                break;
            }

            current_character = string->buffer.data[i + j - search_string->begin_index];

            if(current_character != search_string->data[j])
            {
                is_contains = 0;
                break;
            }
        }

        if(is_contains)
            return 1;
    }

    return 0;
}


procedure applications_listener(Remote_Return *remote_return, Buffer *search_string)
{
    N_32    i;
    N_32    j;
    N_32    contains_count;
    String *current_string;

    printf("applications (\"");

    for(i=0; i<search_string->end_index; ++i)
        printf("%c", search_string->data[i]);

    printf("\")\n");

    contains_count = 0;
    for(i=0; i<applications_source.length; ++i)
    {
        current_string = applications_source.data[i];

        if(string_contains(current_string, search_string))
            ++contains_count;
    }

    add_remote_return_data(remote_return, BEGIN_ARRAY, contains_count);

    for(i=0; i<applications_source.length; ++i)
    {
        current_string = applications_source.data[i];

        if(string_contains(current_string, search_string))
        {
            add_remote_return_data(remote_return, BEGIN_ARRAY, buffer_length(&current_string->buffer));
                for(j=current_string->buffer.begin_index; j<current_string->buffer.end_index; ++j)
                    add_remote_return_data(remote_return, TYPE_N_8, current_string->buffer.data[j]);
            end_remote_return_array(remote_return);
        }
    }

    end_remote_return_array(remote_return);
}


procedure print_applications(char *search_string)
{
    N_32 i;
    N_32 j;
    Buffer  *ret = applications(search_string);

    Buffer **inner_data;
    N_32     inner_data_length;

    Buffer  *inner_buffer;

    inner_data = ret->data;
    inner_data_length = ret->end_index / sizeof(Buffer*);

    printf("%d applications:\n", inner_data_length);

    for(i=0; i<inner_data_length; ++i)
    {
        inner_buffer = inner_data[i];

        printf("\"");

        for(j=0; j<inner_buffer->end_index; ++j)
            printf("%c", inner_buffer->data[j]);

        printf("\"\n");
    }
}


procedure print_description()
{
    Buffer *description_data = description();

    N_32 i;
    N_32 j;

    Buffer **inner_data;
    N_32     inner_data_length;

    Buffer  *inner_buffer;

    inner_data = description_data->data;
    inner_data_length = description_data->end_index / sizeof(Buffer*);

    for(i=0; i<inner_data_length; ++i)
    {
        inner_buffer = inner_data[i];

        for(j=0; j<inner_buffer->end_index; ++j)
            printf("%c", inner_buffer->data[j]);

        inner_buffer = inner_data[i+1];
        ++i;

        for(j=0; j<inner_buffer->end_index; ++j)
            printf("%c", inner_buffer->data[j]);

        printf("\n");
    }
}


procedure parse_application_name(Input *input, String *application_name)
{
    skip_input_spaces(input);

    while(!end_of_input(input) && input_head(input) != '\r' && input_head(input) != '\n')
    {
        write_byte(&application_name->output, input_head(input));
        read_byte(input);
    }

    skip_input_spaces(input);
}


procedure initialize_applications_source()
{
    String *application_name;
    Input   file_input;

    initialize_array(&applications_source, 1, &deinitialize_string);
    initialize_file_input(&file_input, "applications.txt");

    while(!end_of_input(&file_input))
    {
        application_name = new(String);
        initialize_string(application_name);
        parse_application_name(&file_input, application_name);
        add_in_array(&applications_source, application_name);
    }
}


procedure initialize_applications_listener()
{
    Remote_Function_Listener listener;

    initialize_applications_source();

    begin_remote_functions(&listener);
        add_remote_function(&listener, "[1", "applications", &applications_listener);
    end_remote_functions(&listener);

    for(;;);
}

function N_32 main()
{
    initialize_applications_listener();
/*
    Byte buffer[512] = {0};
    printf("input search string: ");
    scanf("%s", buffer);
    print_applications(buffer);
*/
    //print_description();

    return 0;
}
