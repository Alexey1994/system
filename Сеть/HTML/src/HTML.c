static Prefix_Tree *once_tags;


void initialize_HTML_parser()
{
    once_tags = create_prefix_tree();

    add_data_in_prefix_tree(once_tags, "!DOCTYPE", 1);
    add_data_in_prefix_tree(once_tags, "input", 1);
    add_data_in_prefix_tree(once_tags, "link", 1);
    add_data_in_prefix_tree(once_tags, "meta", 1);
    add_data_in_prefix_tree(once_tags, "area", 1);
    add_data_in_prefix_tree(once_tags, "base", 1);
    add_data_in_prefix_tree(once_tags, "br", 1);
    add_data_in_prefix_tree(once_tags, "basefont", 1);
    add_data_in_prefix_tree(once_tags, "bgsound", 1);
    add_data_in_prefix_tree(once_tags, "colgroup", 1);
    add_data_in_prefix_tree(once_tags, "command", 1);
    add_data_in_prefix_tree(once_tags, "col", 1);
    add_data_in_prefix_tree(once_tags, "embed", 1);
    add_data_in_prefix_tree(once_tags, "frame", 1);
    add_data_in_prefix_tree(once_tags, "hr", 1);
    add_data_in_prefix_tree(once_tags, "img", 1);
    add_data_in_prefix_tree(once_tags, "isindex", 1);
    add_data_in_prefix_tree(once_tags, "param", 1);
    add_data_in_prefix_tree(once_tags, "source", 1);
    add_data_in_prefix_tree(once_tags, "wbr", 1);
}


typedef struct
{
    Tag    *current_tag;
    Input  *input;
    Array  *previouse_tags;
}
HTML_parser;


void destroy_tag_structure(DynamicData *data)
{
    switch(data->type)
    {
    case TEXT_DATA:
        destroy_buffer(data->data);
        break;

    case TAG:
        destroy_tag(data->data);
        break;
    }

    free(data);
}


Attribute* create_attribute(Buffer *name, Buffer *data)
{
    Attribute *attribute = new(Attribute);

    attribute->name = name;
    attribute->data = data;

    return attribute;
}


void destroy_attribute(Attribute *attribute)
{
    destroy_buffer(attribute->data);
    destroy_buffer(attribute->name);
    free(attribute);
}


void destroy_tag(Tag *tag)
{
    destroy_buffer(tag->name);
    destroy_prefix_tree(tag->attributes, destroy_attribute);
    destroy_array(tag->structure);
    free(tag);
}


Tag* create_tag(Buffer *name)
{
    Tag *tag=new(Tag);

    tag->is_once = find_data_in_prefix_tree(once_tags, name->data);
    tag->name=name;
    tag->attributes=create_prefix_tree();
    tag->structure=create_array(2, destroy_tag_structure);

    return tag;
}


Boolean is_st(Character c)
{
    if(c=='>' || c=='/')
        return 1;

    return 0;
}


Boolean is_breakeble_character(Character c)
{
    if(is_space(c) || is_st(c))
        return 1;

    return 0;
}


Buffer* read_tag_name(Input *input)
{
    Buffer *tag_name;
    Output  tag_output;

    tag_name = create_buffer(2);
    initialize_buffer_output(tag_name, &tag_output);

    while(!end_of_input(input) && !is_breakeble_character(input->head))
    {
        write_byte(&tag_output, input->head);
        read_byte(input);
    }

    return tag_name;
}


static Buffer* parse_attribute_data(HTML_parser *parser)
{
    Input     *input;
    Buffer    *data;
    Character  close_character;
    Output    *data_output;

    input = parser->input;
    data = create_buffer(2);
    initialize_buffer_output(data, &data_output);

    if(input->head == '=')
    {
        read_byte(input);
        skip_text_input(input);

        if(input->head == '\'' || input->head == '"')
            close_character = input->head;

        read_byte(input);

        while(!end_of_input(input) && input->head != close_character)
        {
            //push_in_string(data, input_stream->head);
            write_byte(&data_output, input->head);
            read_byte(input);
        }

        if(input->head == close_character)
            read_byte(input);
    }

    return data;
}


static void parse_attribute(HTML_parser *parser)
{
    Input     *input;
    Buffer    *attribute_name;
    Output     name_output;
    Buffer    *attribute_data;
    Buffer    *finded_attribute;
    Attribute *attribute;

    input = parser->input;
    skip_text_input(input);

    if(is_st(input->head))
        return;

    attribute_name = create_buffer(2);
    initialize_buffer_output(attribute_name, &name_output);

    while(!end_of_input(input) && !is_st(input->head) && input->head != '=')
    {
        write_byte(&name_output, input->head);
        read_byte(input);
    }

    write_byte(&name_output, '\0');

    attribute_data = parse_attribute_data(parser);
    finded_attribute = find_data_in_prefix_tree(parser->current_tag->attributes, attribute_name->data);

    if(finded_attribute)
        destroy_buffer(finded_attribute);

    attribute = create_attribute(attribute_name, attribute_data);
    add_data_in_prefix_tree(parser->current_tag->attributes, attribute_name->data, attribute);
}


static void parse_attributes(HTML_parser *parser)
{
    Input *input = parser->input;

    while(!end_of_input(input) && !is_st(input->head))
    {
        parse_attribute(parser);
        skip_text_input(input);
    }

    while(!end_of_input(input) && input->head != '>')
        read_byte(input);

    if(!end_of_input(input))
        read_byte(input);
}


static void parse_comment(Input *input)
{
    while(!end_of_input(input) && !read_if_next(input, "-->"))
        read_byte(input);
}


static void parse_text(HTML_parser *parser, Boolean is_empty_tag)
{
    Input  *input          = parser->input;
    Buffer *text;
    Output  text_output;
    Boolean is_skip_spaces = 0;

    text = create_buffer(2);
    initialize_buffer_output(text, &text_output);

    if(is_empty_tag)
        write_byte(&text_output, '<');

    while(!end_of_input(input) && input->head != '<')
    {
        if(is_space(input->head))
        {
            if(!is_skip_spaces)
                write_byte(&text_output, input->head);

            is_skip_spaces = 1;
        }
        else
        {
            write_byte(&text_output, input->head);
            is_skip_spaces = 0;
        }

        read_byte(input);
    }

    add_in_array(parser->current_tag->structure, create_dynamic_data(text, TEXT_DATA));
}


static void parse_open_tag(HTML_parser *parser)
{
    Input  *input;
    Buffer *tag_name;
    Tag    *tag;

    input = parser->input;

    if(is_space(input->head))
        parse_text(parser, 1);

    else if(read_if_next(input, "!--"))
        parse_comment(input);

    else
    {
        tag_name = read_tag_name(input);
        tag = create_tag(tag_name);

        add_in_array(parser->previouse_tags, parser->current_tag);
        add_in_array(parser->current_tag->structure, create_dynamic_data(tag, TAG));
        parser->current_tag = tag;

        parse_attributes(parser);

        if(tag->is_once)
            parser->current_tag = delete_from_array_top(parser->previouse_tags);
    }
}


static void parse_close_tag(HTML_parser *parser)
{
    Input *input;

    input = parser->input;
    read_tag_name(input);

    while(!end_of_input(input) && input->head != '>')
        read_byte(input);

    if(!end_of_input(input))
        read_byte(input);

    if(parser->previouse_tags->length)
        parser->current_tag = delete_from_array_top(parser->previouse_tags);
}


Tag* parse_HTML(Input *input)
{
    HTML_parser *parser = new(HTML_parser);

    Buffer *name_root_tag;
    Output  name_root_tag_output;
    Tag    *root_tag;

    name_root_tag = create_buffer(2);
    initialize_buffer_output(name_root_tag, &name_root_tag_output);

    //copy_char_array_to_string(name_root_tag, "document");
    write_null_terminated_byte_array(&name_root_tag_output, "document");
    root_tag = create_tag(name_root_tag);

    parser->current_tag    = root_tag;
    parser->previouse_tags = create_array(2, 0);
    parser->input          = input;

    while(!end_of_input(input))
    {
        parse_text(parser, 0);

        if(read_if_next(input, "</"))
        {
            parse_close_tag(parser);
        }
        else if(input->head == '<')
        {
            read_byte(input);
            parse_open_tag(parser);
        }

        skip_text_input(input);
    }

    return root_tag;
}


static void write_string(Buffer *string, Output *output)
{
    int i;

    for(i=string->begin_index; i<string->end_index; ++i)
        write_byte(output, string->data[i]);
}


static void print_attributes(Prefix_Tree *attributes, Output *output)
{
    if(!attributes)
        return;

    Attribute *attribute;
    int        i;

    if(attributes->data)
    {
        attribute=attributes->data;

        write_byte(output, ' ');
        write_string(attribute->name, output);
        write_byte(output, '=');
        write_byte(output, '"');
        write_string(attribute->data, output);
        write_byte(output, '"');
    }

    //for(i=0; i<256; i++)
    print_attributes(attributes->prefixes[0], output);
    print_attributes(attributes->prefixes[1], output);
}


void print_html(Tag *root_tag, Output *output)
{
    static int   level=0;
    DynamicData *data;
    Buffer      *text;
    int          i;
    int          j;

    for(i=0; level && i<level-1; i++)
        write_byte(output, '\t');

    if(level)
    {
        write_byte(output, '<');
        write_string(root_tag->name, output);
        print_attributes(root_tag->attributes, output);
        write_byte(output, '>');
        write_byte(output, '\r');
        write_byte(output, '\n');
    }

    if(!root_tag->is_once)
        level++;

    for(i=0; i<root_tag->structure->length; i++)
    {
        data=root_tag->structure->data[i];

        switch(data->type)
        {
            case TAG:
                print_html(data->data, output);
                break;

            case TEXT_DATA:
                text=data->data;

                if(text->end_index - text->end_index)
                    write_string(text, output);
                break;
        }
    }

    if(!root_tag->is_once)
        level--;

    //put_stream_byte(output_stream, '\r');
    //put_stream_byte(output_stream, '\n');

    for(i=0; level && i<level-1; i++)
        write_byte(output, '\t');

    if(level && !root_tag->is_once)
    {
        write_byte(output, '<');
        write_byte(output, '/');
        write_string(root_tag->name, output);
        write_byte(output, '>');
        write_byte(output, '\r');
        write_byte(output, '\n');
    }
}
