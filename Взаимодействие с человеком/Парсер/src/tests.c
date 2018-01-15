#include <stdio.h>
#include "parser.h"


void t(Parser *parser)
{
    print_string(parser->word);
}


PrefixTree* init_keywords()
{
    PrefixTree *keywords = create_prefix_tree();

    add_data_in_prefix_tree(keywords, "if",       t);
    add_data_in_prefix_tree(keywords, "server",     t);
    add_data_in_prefix_tree(keywords, "date",    t);
    add_data_in_prefix_tree(keywords, "Contentlength", t);
    add_data_in_prefix_tree(keywords, "Contenttype",      t);

    return keywords;
}


Boolean dummy_parse_expression(Parser *parser)
{
    print_string(parser->word);

    return 0;
}


void dummy_destroy_language_parser(Byte *language_parser)
{

}


int main()
{
    FILE   *input_file   = fopen("test", "rb");
    Stream *input_stream = create_stream(input_file, fgetc, feof);
    Parser *parser       = create_parser(input_stream,
                                         init_keywords(),
                                         dummy_parse_expression,
                                         is_letter,
                                         0,
                                         dummy_destroy_language_parser);

    parse(parser);
    destroy_parser(parser);

    fclose(input_file);

    return 0;
}

