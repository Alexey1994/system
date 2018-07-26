private procedure destroy_expression_data()
{

}


private function Boolean stack_contains_open_brace(Array *stack)
{
    Z_32 i;

    for(i = stack->length - 1; i >= 0; --i)
        if(stack->data[i] == OPEN_BRACE)
            return 1;

    return 0;
}


procedure initialize_Expression_Parser (
    Expression_Parser *parser,
    function Byte* (*parse_operand)(Input *input),
    procedure (*destroy_opernad)(Byte *operand)
)
{
    initialize_array(&parser->stack, 1, 0);
    initialize_array(&parser->unary_operations, 1, 0);
    initialize_array(&parser->binary_operations, 1, 0);

    parser->parse_operand   = parse_operand;
    parser->destroy_opernad = destroy_opernad;
}


private function Unary_Operation* create_unary_operation(Character *name, N_32 number)
{
    Unary_Operation *operation;

    operation = new(Unary_Operation);

    operation->name   = name;
    operation->number = number;

    return operation;
}


private procedure destroy_unary_operation(Unary_Operation *operation)
{
    free(operation);
}


private function Binary_Operation* create_binary_operation(Character *name, N_32 number, Z_32 priority)
{
    Binary_Operation *operation;

    operation = new(Binary_Operation);

    operation->name     = name;
    operation->number   = number;
    operation->priority = priority;

    return operation;
}


private procedure destroy_binary_operation(Binary_Operation *operation)
{
    free(operation);
}


procedure add_unary_operation (Expression_Parser *parser, Character *text, N_32 code)
{
    add_in_array(&parser->unary_operations, create_unary_operation(text, code));
}


procedure add_binary_operation (Expression_Parser *parser, Character *text, N_32 code, N_32 priority)
{
    add_in_array(&parser->binary_operations, create_binary_operation(text, code, priority));
}


procedure deinitialize_Expression_Parser (Expression_Parser *parser)
{
    deinitialize_array(&parser->stack);
    deinitialize_array(&parser->unary_operations);
    deinitialize_array(&parser->binary_operations);
}


private function N_32 binary_operation_priority(Expression_Parser *parser, N_32 operation_number)
{
    N_32 i;

    for(i=0; i<parser->binary_operations.length; ++i)
        if(((Binary_Operation*)parser->binary_operations.data[i])->number == operation_number)
            return ((Binary_Operation*)parser->binary_operations.data[i])->priority;

    return 0;
}


function Boolean parse_expression(Expression_Parser *parser, Input *input, Array *expression)
{
    N_32              i;
    Unary_Operation  *current_unary_operation;
    Binary_Operation *current_binary_operation;
    Dynamic_Data     *dynamic_data;
    Byte             *operand;
    Boolean           is_expression;
    Boolean           is_operation;
    Boolean           is_close_brace;

    is_expression  = 1;
    is_operation   = 0;
    is_close_brace = 0;

    clear_array(&parser->stack);
    skip_input_spaces(input);

    while(!end_of_input(input) && is_expression)
    {
        if(!is_close_brace)
        {
            next_unary_operation:
                skip_input_spaces(input);

                if(end_of_input(input))
                    break;

                for(i=0; i<parser->unary_operations.length; ++i)
                {
                    current_unary_operation = parser->unary_operations.data[i];

                    if(read_if_next(input, current_unary_operation->name))
                    {
                        dynamic_data = new(Dynamic_Data);
                        initialize_dynamic_data(dynamic_data, current_unary_operation, UNARY_OPERATION);
                        add_in_array(expression, dynamic_data);
                        goto next_unary_operation;
                    }
                }

            if(input_head(input) != '(')
            {
                operand = parser->parse_operand(input);

                if(!operand)
                    goto error;

                dynamic_data = new(Dynamic_Data);
                initialize_dynamic_data(dynamic_data, operand, OPERAND);
                add_in_array(expression, dynamic_data);
                is_operation = 0;
            }
        }

        skip_input_spaces(input);

        switch(input_head(input))
        {
            case '(':
                add_in_array(&parser->stack, OPEN_BRACE);
                read_byte(input);

                is_operation = 1;
                is_close_brace = 0;
                break;

            case ')':
                if(!stack_contains_open_brace(&parser->stack))
                {
                    is_expression = 0;
                    break;
                }

                if(array_top(&parser->stack) == OPEN_BRACE)
                    goto error;

                do
                {
                    if(!parser->stack.length)
                        goto error;

                    dynamic_data = new(Dynamic_Data);
                    initialize_dynamic_data(dynamic_data, delete_from_array_top(&parser->stack), BINARY_OPERATION);
                    add_in_array(expression, dynamic_data);
                }
                while(array_top(&parser->stack) != OPEN_BRACE);

                delete_from_array_top(&parser->stack);
                read_byte(input);

                is_operation = 0;
                is_close_brace = 1;
                break;

            default:
                is_expression = 0;

                for(i=0; i<parser->binary_operations.length; ++i)
                {
                    current_binary_operation = parser->binary_operations.data[i];

                    if(read_if_next(input, current_binary_operation->name))
                    {
                        if(is_operation)
                            goto error;

                        while(
                            parser->stack.length && array_top(&parser->stack) != OPEN_BRACE &&
                            ((Binary_Operation*)array_top(&parser->stack))->priority >= current_binary_operation->priority
                        )
                        {
                            dynamic_data = new(Dynamic_Data);
                            initialize_dynamic_data(dynamic_data, delete_from_array_top(&parser->stack), BINARY_OPERATION);
                            add_in_array(expression, dynamic_data);
                        }

                        add_in_array(&parser->stack, current_binary_operation);

                        is_operation = 1;
                        is_close_brace = 0;
                        is_expression = 1;
                    }
                }
        }

        skip_input_spaces(input);
    }

    while(parser->stack.length)
    {
        current_binary_operation = delete_from_array_top(&parser->stack);

        if(current_binary_operation == OPEN_BRACE)
            goto error;

        dynamic_data = new(Dynamic_Data);
        initialize_dynamic_data(dynamic_data, current_binary_operation, BINARY_OPERATION);
        add_in_array(expression, dynamic_data);
    }

    return 1;

error:
    return 0;
}


void print_expression_in_postfix_notation(Expression_Parser *parser, Array *expression)
{
    int               i;
    Dynamic_Data     *expression_node;
    Binary_Operation *binary_operation;
    Unary_Operation  *unary_operation;

    for(i=0; i<expression->length; i++)
    {
        expression_node = expression->data[i];

        switch(expression_node->type)
        {
        case BINARY_OPERATION:
            binary_operation = expression_node->data;
            printf("%s ", binary_operation->name);
            break;

        case UNARY_OPERATION:
            unary_operation = expression_node->data;
            printf("%s ", unary_operation->name);
            break;

        case OPERAND:
            printf("%d ", expression_node->data);
            break;
        }
    }
}
