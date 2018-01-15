function Array* create_array(N_32 reserve, procedure (*destroy_node)(Byte *node))
{
    Array *array;

    array = new(Array);
    initialize_array(array, reserve, destroy_node);

    return array;
}


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


procedure destroy_array(Array *array)
{
    deinitialize_array(array);
    free_memory(array);
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
    N_32   i;
    Byte **data;
    N_32   length;

    data = array->data;
    length = array->length;

    for(i=0; i<length; ++i)
        crawl_func(data[i]);
}


private function Byte* get_array_structure_element(Random_Access_Structure *structure, N_32 pos)
{
    Array *array;

    array = structure->structure;

    if(pos >= array->length)
    {
        //printf("out of range in array (length of array is %d)\n", array->length);
        goto error;
    }

    return array->data[pos];

error:
    //printf("error in get_array_structure_element\n");
    //printf("out of range in array (length of array is %d)\n", array->length);

    return 0;
}


private function N_32 get_array_structure_length(Random_Access_Structure *structure)
{
    Array *array = structure->structure;
    return array->length;
}


function Random_Access_Structure* create_array_structure(Array *array)
{
    return create_random_access_structure(array, get_array_structure_element, get_array_structure_length);
}


procedure destroy_array_structure(Random_Access_Structure *structure)
{
    destroy_random_access_structure(structure);
    destroy_array(structure->structure);
}
