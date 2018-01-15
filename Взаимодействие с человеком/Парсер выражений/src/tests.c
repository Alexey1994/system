#include <stdio.h>
#include "expression parser.h"


#define BINARY_PLUS 0
#define BINARY_MUL  1

#define UNARY_MINUS 2

Operation* create_operation(Character *name, Byte number)
{
    Operation *operation = new(Operation);

    operation->name   = name;
    operation->number = number;

    return operation;
}


void destroy_operation(Operation *operation)
{
    free(operation);
}


Array* get_unary_operations()
{
    Array     *unary_operations = create_array(1, destroy_operation);

    push_in_array(unary_operations, create_operation("-", UNARY_MINUS));

    return unary_operations;
}


Array* get_binary_operations()
{
    Array *binary_operations = create_array(2, destroy_operation);

    push_in_array(binary_operations, create_operation("+", BINARY_PLUS));
    push_in_array(binary_operations, create_operation("*", BINARY_MUL));

    return binary_operations;
}


int* get_binary_priorities()
{
    int *binary_priorities = new_array(int, 256);

    binary_priorities[OPEN_BRACE]  = 0;
    binary_priorities[BINARY_PLUS] = 3;
    binary_priorities[BINARY_MUL]  = 4;

    return binary_priorities;
}


Boolean get_operand(Stream *input_stream)
{
    int number = get_text_stream_uint(input_stream);

    return number;

error:
    return 0;
}


Character* get_operations_translator()
{
    Character **codes = new_array(Character*, 3);

    codes[BINARY_PLUS] = " add ";
    codes[BINARY_MUL]  = " mul ";
    codes[UNARY_MINUS] = " sub ";

    return codes;
}


void print_operand(int operand)
{
    printf("%d ", operand);
}


int main()
{
    FILE   *input_file   = fopen("test", "rb");
    Stream *input_stream = create_stream(input_file, fgetc, feof);

    Array  *expression   = parse_expression_in_infix_notation(input_stream,
                                                              get_unary_operations(),
                                                              get_binary_operations(),
                                                              get_binary_priorities(),
                                                              input_stream,
                                                              get_operand);

    print_expression_in_postfix_notation(expression, get_operations_translator(), print_operand);

    fclose(input_file);

    return 0;
}
