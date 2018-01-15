#include <libs/extends/extends.h>
#include <libs/input/input.h>
#include <libs/output/output.h>

#define destroy_string()
#define skip_text_stream()
#define get_stream_byte()
#define read_if_on_stream_head()
#define create_string()
#define end_stream()

procedure skip_text_input(Input *input)
{
    while(is_space(input->head))
        read_byte(input);
}

function Boolean read_if_next(Input *input, Byte *head)
{
    return 0;
}

procedure write_null_terminated_byte_array(Output *output, Byte *array)
{
    for(; *array; ++array)
        write_byte(output, *array);
}

#include <stdio.h>
#include "HTML.h"


void put_file_byte(FILE *file_out, Byte byte)
{
    printf("%c", byte);
    fputc(byte, file_out);
}


int main()
{
    FILE   *file_in;
    FILE   *file_out;
    Tag    *document;
    Input   input;
    Output  output;

    file_in = fopen("a.html", "rb");
    initialize_input(&input, file_in, fgetc, feof);

    file_out = fopen("b.html", "wb");
    initialize_output(&output, file_out, put_file_byte);

    initialize_HTML_parser();
    document = parse_HTML(&input);

    printf("\n");
    print_html(document, &output);

    return 0;
}

