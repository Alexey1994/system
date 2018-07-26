#ifndef EXPRESSION_PARSER_H_INCLUDED
#define EXPRESSION_PARSER_H_INCLUDED


#include <data structures/character/character.h>
#include <data structures/array/array.h>
#include <input/input.h>
//#include <stream/stream.h>
//#include <error/error.h>


#define OPEN_BRACE  0


typedef struct
{
    //Array expression;
    Array stack;
    Array unary_operations;
    Array binary_operations;

    function Byte* (*parse_operand)   (Input *input);
    procedure      (*destroy_opernad) (Byte *operand);
}
Expression_Parser;


typedef struct
{
    Character *name;
    N_32       number;
}
Unary_Operation;


typedef struct
{
    Character *name;
    N_32       number;
    N_32       priority;
}
Binary_Operation;


typedef enum
{
    BINARY_OPERATION = 1,
    UNARY_OPERATION  = 2,
    OPERAND          = 3
}
Operation_Type;


//procedure         initialize_Expression_Parser   (Expression_Parser *parser, function Byte* (*parse_operand)(Input *input));
procedure         add_unary_operation            (Expression_Parser *parser, Character *text, N_32 code);
procedure         add_binary_operation           (Expression_Parser *parser, Character *text, N_32 code, N_32 priority);
function  Boolean parse_expression               (Expression_Parser *parser, Input *input, Array *expression);
procedure         deinitialize_Expression_Parser (Expression_Parser *parser);

/*
function Array* parse_expression_in_infix_notation(
    Stream *input_stream,
    Array  *unary_operations,
    Array  *binary_operations,
    Z_32   *binary_priorities,
    Byte   *language_parser,
    function Byte* (*get_operand)(Byte *language_parser)
);

procedure print_expression_in_postfix_notation(
    Array *expression,
    Character **operations_translator,
    procedure(*print_operand)(Byte *operand)
);
*/

#include "expression parser.c"

#endif // EXPRESSION_PARSER_H_INCLUDED
