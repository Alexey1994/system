static void destroy_expression_data()
{

}


static Boolean stack_contains_open_brace(Array *stack)
{
    int    i=stack->length-1;
    char **data=stack->data;

    for(; i>=0; i--)
        if(data[i] == OPEN_BRACE)
            return 1;

    return 0;
}


Array* parse_expression_in_infix_notation(Stream *input_stream,
                                          Array  *unary_operations,
                                          Array  *binary_operations,
                                          int    *binary_priorities,
                                          Byte   *language_parser,
                                          Byte* (*get_operand)(Byte *language_parser))
{
    Array     *stack              = create_array(4, 0);
    Array     *expression         = create_array(4, destroy_expression_data);
    Boolean    is_expression      = 1;
    Boolean    is_operation       = 0;
    Boolean    is_close_brace     = 0;
    Boolean    is_unary_operation;
    Byte       operation_number;
    Operation *operation;
    Byte      *operand;
    int        i;

    while(!end_stream(input_stream) && is_expression)
    {
        if(!is_close_brace)
        {
            do
            {
                is_unary_operation = 0;
                skip_text_stream(input_stream);

                for(i=0; i<unary_operations->length; i++)
                {
                    operation = unary_operations->data[i];

                    if(read_if_on_stream_head(input_stream, operation->name))
                    {
                        push_in_array(expression, create_dynamic_data(operation->number, UNARY_OPERATION));
                        is_unary_operation=1;
                        break;
                    }

                    skip_text_stream(input_stream);
                }
            }
            while(is_unary_operation);
        }

        if(input_stream->head!='(' && !is_close_brace)
        {
            operand = get_operand(language_parser);

            if(!operand)
                goto error;

            push_in_array(expression, create_dynamic_data(operand, OPERAND));
            is_operation=0;
        }

        switch(input_stream->head)
        {
        case '(':
            push_in_array(stack, OPEN_BRACE);
            get_stream_byte(input_stream);

            is_operation=1;
            is_close_brace=0;
            break;

        case ')':
            if(!stack_contains_open_brace(stack))
            {
                is_expression=0;
                break;
            }

            if(get_array_top(stack) == OPEN_BRACE)
            {
                print_error("braces without expression\n");
                goto error;
            }

            do
            {
                if(!stack->length)
                {
                    printf("expected (\n");
                    goto error;
                }

                push_in_array(expression, create_dynamic_data(pop_from_array(stack), BINARY_OPERATION));
            }
            while(get_array_top(stack) != OPEN_BRACE);

            pop_from_array(stack);
            get_stream_byte(input_stream);

            is_operation = 0;
            is_close_brace = 1;
            break;

        default:
            is_expression = 0;

            for(i=0; i<binary_operations->length; i++)
            {
                operation = binary_operations->data[i];

                if(read_if_on_stream_head(input_stream, operation->name))
                {
                    if(is_operation)
                    {
                        print_error("2 operations without operand\n");
                        goto error;
                    }

                    while(stack->length && binary_priorities[(int)get_array_top(stack)] >= binary_priorities[(int)operation->number])
                        push_in_array(expression, create_dynamic_data(pop_from_array(stack), BINARY_OPERATION));

                    push_in_array(stack, operation->number);

                    is_operation=1;
                    is_close_brace=0;
                    is_expression=1;
                }
            }
        }

        skip_text_stream(input_stream);
    }

    while(stack->length)
    {
        operation_number = pop_from_array(stack);

        if(operation_number == OPEN_BRACE)
        {
            print_error("expected )\n");
            goto error;
        }

        push_in_array(expression, create_dynamic_data(operation_number, BINARY_OPERATION));
    }

    destroy_array(stack);
    return expression;

error:
    destroy_array(stack);
    destroy_array(expression);
    return 0;
}


void print_expression_in_postfix_notation(Array *expression,
                                          Character **operations_translator,
                                          void(*print_operand)(Byte *operand))
{
    int          i;
    DynamicData *expression_node;

    for(i=0; i<expression->length; i++)
    {
        expression_node = expression->data[i];

        switch(expression_node->type)
        {
        case BINARY_OPERATION:
            printf("%s", operations_translator[(int)expression_node->data]);
            break;

        case UNARY_OPERATION:
            printf("%s", operations_translator[(int)expression_node->data]);
            break;

        case OPERAND:
            print_operand(expression_node->data);
            break;
        }
    }
}
