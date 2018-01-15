function Prefix_Tree* create_prefix_tree()
{
    Prefix_Tree *new_node;

    new_node = new(Prefix_Tree);

    new_node->prefixes[0] = 0;
    new_node->prefixes[1] = 0;
    new_node->data        = 0;

    return new_node;
}


procedure destroy_prefix_tree(Prefix_Tree *tree, procedure (*destroy_data)(Byte *data))
{
    if(tree->prefixes[0])
        destroy_prefix_tree(tree->prefixes[0], destroy_data);

    if(tree->prefixes[1])
        destroy_prefix_tree(tree->prefixes[1], destroy_data);

    if(destroy_data && tree->data)
        destroy_data(tree->data);

    free_memory(tree->prefixes);
    free_memory(tree);
}


procedure add_in_prefix_tree(Prefix_Tree *tree, Byte *key, Byte *value)
{
    Byte current_index;

    for(; *key; ++key)
    {
        for(current_index = 0b10000000; current_index; current_index >>= 1)
        {
            if(current_index & *key)
            {
                if(!tree->prefixes[1])
                    tree->prefixes[1] = create_prefix_tree();

                tree = tree->prefixes[1];
            }
            else
            {
                if(!tree->prefixes[0])
                    tree->prefixes[0] = create_prefix_tree();

                tree = tree->prefixes[0];
            }
        }
    }

    tree->data = value;
}


function Byte* find_in_prefix_tree(Prefix_Tree *tree, Byte *key)
{
    Byte current_index;

    for(; *key; ++key)
    {
        for(current_index = 0b10000000; current_index; current_index >>= 1)
        {
            if(current_index & *key)
                tree = tree->prefixes[1];
            else
                tree = tree->prefixes[0];

            if(!tree)
                return 0;
        }
    }

    return tree->data;
}


private procedure crawl_prefix_tree_node(Prefix_Tree *tree, procedure (*element)(Byte *element, String *key, Byte *arguments), Byte *arguments, String *key, Byte current_index)
{
    Byte key_top;

    if(!current_index)
    {
        write_byte(&key->output, 0);
        current_index = 0b10000000;
    }

    key_top = key->buffer.data[ key->buffer.end_index-1 ];

    if(tree->prefixes[0])
        crawl_prefix_tree_node(tree->prefixes[0], element, arguments, key, current_index>>1);

    if(tree->prefixes[1])
    {
        key->buffer.data[ key->buffer.end_index-1 ] = key_top | current_index;
        crawl_prefix_tree_node(tree->prefixes[1], element, arguments, key, current_index>>1);
    }

    if(tree->data)
        element(tree->data, key, arguments);

    if(current_index == 0b10000000)
    {
        --key->buffer.end_index;
        key->buffer.data[ key->buffer.end_index ] = key_top;
    }
}


procedure crawl_prefix_tree (Prefix_Tree *tree, procedure (*element)(Byte *element, String *key, Byte *arguments), Byte *arguments)
{
    String key;
    Byte   current_index;

    initialize_string(&key);
    write_in_buffer(&key.buffer, 0);
    current_index = 0b10000000;
    crawl_prefix_tree_node(tree, element, arguments, &key, current_index);
    deinitialize_string(&key);
}
