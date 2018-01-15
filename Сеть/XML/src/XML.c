#include "XML.h"


typedef struct
{
    XML_Tag  *current_tag;
    Stream   *input_stream;
    Array    *previouse_tags;
}
XML_parser;


void destroy_tag_structure(DynamicData *data)
{
    switch(data->type)
    {
    case TEXT_DATA:
        destroy_string(data->data);
        break;

    case TAG:
        destroy_tag(data->data);
        break;
    }

    free(data);
}


Attribute* create_attribute(String *name, String *data)
{
    Attribute *attribute = new(Attribute);

    attribute->name = name;
    attribute->data = data;

    return attribute;
}


void destroy_attribute(Attribute *attribute)
{
    destroy_string(attribute->data);
    destroy_string(attribute->name);
    free(attribute);
}


void destroy_tag(XML_Tag *tag)
{
    destroy_string(tag->name);
    destroy_prefix_tree(tag->attributes, destroy_attribute);
    destroy_array(tag->structure);
    free(tag);
}


XML_Tag* create_tag(String *name)
{
    XML_Tag *tag=new(XML_Tag);

    tag->name       = name;
    tag->attributes = create_prefix_tree();
    tag->structure  = create_array(2, destroy_tag_structure);

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


String* read_tag_name(Stream *input_stream)
{
    String *tag_name = create_string(2);

    while(!end_stream(input_stream) && !is_breakeble_character(input_stream->head))
    {
        push_in_string(tag_name, input_stream->head);
        get_stream_byte(input_stream);
    }

    return tag_name;
}


static String* parse_attribute_data(XML_parser *parser)
{
    Character  close_character;

    Stream    *input_stream    = parser->input_stream;
    String    *data            = create_string(2);

    if(input_stream->head=='=')
    {
        get_stream_byte(input_stream);
        skip_text_stream(input_stream);

        if(input_stream->head=='\'' || input_stream->head=='"')
            close_character=input_stream->head;

        get_stream_byte(input_stream);

        while(!end_stream(input_stream) && input_stream->head!=close_character)
        {
            push_in_string(data, input_stream->head);
            get_stream_byte(input_stream);
        }

        if(input_stream->head == close_character)
            get_stream_byte(input_stream);
    }

    return data;
}


static void parse_attribute(XML_parser *parser)
{
    String    *attribute_name;
    String    *attribute_data;
    String    *finded_attribute;
    Attribute *attribute;

    Stream *input_stream = parser->input_stream;

    skip_text_stream(input_stream);

    if(is_st(input_stream->head))
        return;

    attribute_name=create_string(2);

    while(!end_stream(input_stream) && !is_st(input_stream->head) && input_stream->head!='=')
    {
        push_in_string(attribute_name, input_stream->head);
        get_stream_byte(input_stream);
    }


    attribute_data = parse_attribute_data(parser);
    finded_attribute = find_data_in_prefix_tree(parser->current_tag->attributes, attribute_name->begin);

    if(finded_attribute)
        destroy_string(finded_attribute);

    attribute = create_attribute(attribute_name, attribute_data);
    add_data_in_prefix_tree(parser->current_tag->attributes, attribute_name->begin, attribute);
}


static void parse_attributes(XML_parser *parser)
{
    Stream *input_stream = parser->input_stream;

    while(!end_stream(input_stream) && !is_st(input_stream->head))
    {
        parse_attribute(parser);
        skip_text_stream(input_stream);
    }

    while(!end_stream(input_stream) && input_stream->head!='>')
        get_stream_byte(input_stream);

    if(!end_stream(input_stream))
        get_stream_byte(input_stream);
}


static void parse_comment(Stream *input_stream)
{
    while(!end_stream(input_stream) && !read_if_on_stream_head(input_stream, "-->"))
        get_stream_byte(input_stream);
}


static void parse_text(XML_parser *parser, Boolean is_empty_tag)
{
    Stream *input_stream   = parser->input_stream;
    String *text           = create_string(2);
    Boolean is_skip_spaces = 0;

    if(is_empty_tag)
        push_in_string(text, '<');

    while(!end_stream(input_stream) && input_stream->head!='<')
    {
        if(is_space(input_stream->head))
        {
            if(!is_skip_spaces)
                push_in_string(text, input_stream->head);

            is_skip_spaces=1;
        }
        else
        {
            push_in_string(text, input_stream->head);
            is_skip_spaces=0;
        }

        get_stream_byte(input_stream);
    }

    push_in_array(parser->current_tag->structure, create_dynamic_data(text, TEXT_DATA));
}


static void parse_open_tag(XML_parser *parser)
{
    Stream   *input_stream = parser->input_stream;
    String   *tag_name;
    XML_Tag  *tag;

    if(is_space(input_stream->head))
        parse_text(parser, 1);

    else if(read_if_on_stream_head(input_stream, "!--"))
        parse_comment(input_stream);

    else
    {
        tag_name = read_tag_name(input_stream);
        tag = create_tag(tag_name);

        push_in_array(parser->previouse_tags, parser->current_tag);
        push_in_array(parser->current_tag->structure, create_dynamic_data(tag, TAG));
        parser->current_tag=tag;

        parse_attributes(parser);
/*
        if(tag->is_once)
            parser->current_tag = pop_from_array(parser->previouse_tags);*/
    }
}


static void parse_close_tag(XML_parser *parser)
{
    Stream *input_stream = parser->input_stream;

    read_tag_name(input_stream);

    while(!end_stream(input_stream) && input_stream->head!='>')
        get_stream_byte(input_stream);

    if(!end_stream(input_stream))
        get_stream_byte(input_stream);

    if(parser->previouse_tags->length)
        parser->current_tag = pop_from_array(parser->previouse_tags);
}


XML_Tag* parse_XML(Stream *input_stream)
{
    XML_parser *parser = new(XML_parser);

    String  *name_root_tag = create_string(2);
    XML_Tag *root_tag;

    copy_char_array_to_string(name_root_tag, "XML");
    root_tag=create_tag(name_root_tag);

    parser->current_tag    = root_tag;
    parser->previouse_tags = create_array(2, 0);
    parser->input_stream   = input_stream;

    while(!end_stream(input_stream))
    {
        parse_text(parser, 0);

        if(read_if_on_stream_head(input_stream, "</"))
        {
            parse_close_tag(parser);
        }
        else if(input_stream->head=='<')
        {
            get_stream_byte(input_stream);
            parse_open_tag(parser);
        }

        skip_text_stream(input_stream);
    }

    return root_tag;
}


static void write_string(String *string, Stream *output_stream)
{
    int i;

    for(i=0; i<string->length; i++)
        put_stream_byte(output_stream, string->begin[i]);
}


static void print_attributes(PrefixTree *attributes, Stream *output_stream)
{
    if(!attributes)
        return;

    Attribute *attribute;
    int        i;

    if(attributes->data)
    {
        attribute=attributes->data;

        put_stream_byte(output_stream, ' ');
        write_string(attribute->name, output_stream);
        put_stream_byte(output_stream, '=');
        put_stream_byte(output_stream, '"');
        write_string(attribute->data, output_stream);
        put_stream_byte(output_stream, '"');
    }

    for(i=0; i<256; i++)
        print_attributes(attributes->prefixes[i], output_stream);
}


void print_formatted_XML(XML_Tag *root_tag, Stream *output_stream)
{
    static int   level=0;
    DynamicData *data;
    String      *text;
    int          i;
    int          j;

    for(i=0; level && i<level-1; i++)
        put_stream_byte(output_stream, '\t');

    put_stream_byte(output_stream, '<');
    write_string(root_tag->name, output_stream);
    print_attributes(root_tag->attributes, output_stream);
    put_stream_byte(output_stream, '>');
    put_stream_byte(output_stream, '\r');
    put_stream_byte(output_stream, '\n');

    for(j=0; level && j<level-1; ++j)
        put_stream_byte(output_stream, '\t');

    level++;

    for(i=0; i<root_tag->structure->length; i++)
    {
        data=root_tag->structure->data[i];

        switch(data->type)
        {
            case TAG:
                print_formatted_XML(data->data, output_stream);
                break;

            case TEXT_DATA:
                put_stream_byte(output_stream, '\t');

                text=data->data;

                if(text->length)
                    write_string(text, output_stream);

                put_stream_byte(output_stream, '\r');
                put_stream_byte(output_stream, '\n');
                break;
        }
    }

    level--;

    for(i=0; level && i<level-1; i++)
        put_stream_byte(output_stream, '\t');

    put_stream_byte(output_stream, '<');
    put_stream_byte(output_stream, '/');
    write_string(root_tag->name, output_stream);
    put_stream_byte(output_stream, '>');
    put_stream_byte(output_stream, '\r');
    put_stream_byte(output_stream, '\n');
}


void print_XML(XML_Tag *root_tag, Stream *output_stream)
{
    DynamicData *data;
    String      *text;
    int          i;

    put_stream_byte(output_stream, '<');
    write_string(root_tag->name, output_stream);
    print_attributes(root_tag->attributes, output_stream);
    put_stream_byte(output_stream, '>');

    for(i=0; i<root_tag->structure->length; i++)
    {
        data=root_tag->structure->data[i];

        switch(data->type)
        {
            case TAG:
                print_XML(data->data, output_stream);
                break;

            case TEXT_DATA:
                text=data->data;

                if(text->length)
                    write_string(text, output_stream);
                break;
        }
    }

    put_stream_byte(output_stream, '<');
    put_stream_byte(output_stream, '/');
    write_string(root_tag->name, output_stream);
    put_stream_byte(output_stream, '>');
}


XML_Tag* find_XML_tag_in_childs(XML_Tag *parent, char *tag_name)
{
    DynamicData *data;
    XML_Tag     *current_child;
    int          i;

    Array *childs = parent->structure;

    for(i=0; i<childs->length; ++i)
    {
        data = childs->data[i];

        if(data->type != TAG)
            continue;

        current_child = data->data;

        if(!strcmp(tag_name, current_child->name->begin))
            return current_child;
    }

    return 0;
}


Array* find_all_XML_tags_in_childs(XML_Tag *parent, char *tag_name)
{
    DynamicData *data;
    XML_Tag     *current_child;
    int          i;

    Array *finded_tags = create_array(1, 0);
    Array *childs      = parent->structure;

    for(i=0; i<childs->length; ++i)
    {
        data = childs->data[i];

        if(data->type != TAG)
            continue;

        current_child = data->data;

        if(!strcmp(tag_name, current_child->name->begin))
            push_in_array(finded_tags, current_child);
    }

    return finded_tags;
}


Attribute* get_XML_Tag_attribute(XML_Tag *tag, char *attribute_name)
{
    return find_data_in_prefix_tree(tag->attributes, attribute_name);
}
