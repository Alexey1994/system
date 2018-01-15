void skip_spaces(Parser *parser)
{
    skip_text_stream(parser->input_stream);
}


static Boolean read_initialized_word(Parser *parser, String *word)
{
    Stream   *input_stream                   = parser->input_stream;
    Boolean (*is_parser_letter)(Character c) = parser->is_letter;

    skip_text_stream(input_stream);

    if(!is_letter(input_stream->head))
        return 0;

    while(!end_stream(input_stream) && is_parser_letter(input_stream->head))
    {
        push_in_string(word, input_stream->head);
        get_stream_byte(input_stream);
    }

    return 1;
}


String* read_new_word(Parser *parser)
{
    String *word = create_string(2);

    if(read_initialized_word(parser, word))
        return word;

    destroy_string(word);
    return 0;
}


String* read_word(Parser *parser, String *word)
{
    clear_string(word);

    if(read_initialized_word(parser, word))
        return word;

    return 0;
}
