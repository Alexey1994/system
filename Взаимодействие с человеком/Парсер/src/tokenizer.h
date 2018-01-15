#ifndef TOKENIZER_H_INCLUDED
#define TOKENIZER_H_INCLUDED


#include <libs/data structures/character/character.h>
#include <libs/data structures/string/string.h>
#include <libs/error/error.h>


String* read_new_word(Parser *parser);
String* read_word(Parser *parser, String *word);
void skip_spaces(Parser *parser);


#include "tokenizer.c"

#endif // TOKENIZER_H_INCLUDED
