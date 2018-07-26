private procedure free_array_data(Array *array)
{
    N_32        i;
    N_32        length;
    Byte      **data;
    procedure (*destroy_node)(Byte *node);

    length = array->length;
    data = array->data;
    destroy_node = array->destroy_node;

    for(i=0; i<length; i++)
        destroy_node(data[i]);
}


procedure initialize_array (Array *array, N_32 reserve, procedure (*destroy_node)(Byte *node))
{
    array->reserve       = reserve;
    array->buffer_length = reserve;
    array->data          = new_array(Byte*, reserve);
    array->length        = 0;
    array->destroy_node  = destroy_node;
}


procedure deinitialize_array (Array *array)
{
    if(array->destroy_node)
        free_array_data(array);

    free_memory(array->data);
}


procedure clear_array (Array *array)
{
    array->length = 0;
}


procedure add_in_array(Array *array, Byte *data)
{
    if(array->length == array->buffer_length)
    {
        Byte **old_data      = array->data;
        N_32   old_data_size = array->buffer_length;
        N_32   i;

        array->buffer_length += array->reserve;
        array->data = new_array(Byte*, array->buffer_length);

        for(i=0; i<old_data_size; ++i)
            array->data[i] = old_data[i];

        //reallocate_array(array->data, Byte*, array->buffer_length);
    }

    array->data[array->length] = data;
    ++array->length;
}


function Byte* delete_from_array_top(Array *array)
{
    --array->length;
    return array->data[array->length];
}


function Byte* array_top(Array *array)
{
    if(!array->length)
        return 0;

    return array->data[ array->length-1 ];
}


function Byte* array_data(Array *array, N_32 index)
{
    if(index >= array->length)
        return 0;

    return array->data[index];
}


procedure crawl_array(Array *array, procedure (*crawl_func)(Byte *node))
{
    N_32 i;

    for(i=0; i<array->length; ++i)
        crawl_func(array->data[i]);
}