#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include <libs/stream/stream.h>
#include <libs/data structures/prefix tree/prefix tree.h>
#include <libs/data structures/string/string.h>


typedef struct
{
    Stream      *input_stream;
    String      *word;

    Boolean    (*is_letter)(Character c);

    PrefixTree  *keywords;
    Boolean    (*parse_expression)(struct Parser *parser);
    Byte        *language_parser;
    void       (*destroy_language_parser)(Byte *language_parser);
}
Parser;


Parser* create_parser(Stream      *input_stream,
                      PrefixTree  *keywords,
                      Boolean    (*parse_expression)(Parser *parser),
                      Boolean    (*is_letter)(Character c),
                      Byte        *language_parser,
                      void       (*destroy_language_parser)(Byte *language_parser));

void    destroy_parser(Parser *parser);
Boolean parse(Parser *parser);


#include "tokenizer.h"
#include "parser.c"

#endif // PARSER_H_INCLUDED
