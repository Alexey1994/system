Parser* create_parser(Stream      *input_stream,
                      PrefixTree  *keywords,
                      Boolean    (*parse_expression)(Parser *parser),
                      Boolean    (*is_letter)(Character c),
                      Byte        *language_parser,
                      void       (*destroy_language_parser)(Byte *language_parser))
{
    Parser *parser = new(Parser);

    parser->input_stream            = input_stream;
    parser->is_letter               = is_letter;
    parser->word                    = create_string(2);
    parser->keywords                = keywords;
    parser->parse_expression        = parse_expression;
    parser->language_parser         = language_parser;
    parser->destroy_language_parser = destroy_language_parser;

    return parser;
}


void destroy_parser(Parser *parser)
{
    parser->destroy_language_parser(parser->language_parser);
    free(parser);
}


Boolean parse(Parser *parser)
{
    Stream      *input_stream                             = parser->input_stream;
    PrefixTree  *keywords                                 = parser->keywords;
    Boolean    (*parse_expression)(struct Parser *parser) = parser->parse_expression;
    Boolean    (*keyword_func)(Parser *parser);

    while(!end_stream(input_stream))
    {
        if(read_word(parser, parser->word))
        {
            keyword_func=find_data_in_prefix_tree(keywords, parser->word->begin);

            if(keyword_func)
            {
                if(!keyword_func(parser))
                    goto error;
            }
            else if(!parse_expression(parser))
                goto error;
        }
        else if(!parse_expression(parser))
            goto error;
    }

    return 1;

error:
    return 0;
}
