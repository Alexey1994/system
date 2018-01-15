/*
#include <stdio.h>
#include "XML.h"


void put_file_byte(FILE *file_out, Byte byte)
{
    printf("%c", byte);
    fputc(byte, file_out);
}


int main()
{
    XML_Tag *document;

    FILE    *file_in       = fopen("a.xml", "rb");
    FILE    *file_out      = fopen("b.xml", "wb");
    Stream  *input_stream  = create_stream(file_in, fgetc, feof);
    Stream  *output_stream = create_output_stream(file_out, put_file_byte);

    //initialize_HTML_parser();
    document = parse_XML(input_stream);

    printf("\n");
    print_formatted_XML(document, output_stream);
    print_XML(document, output_stream);

    printf("\n");
    XML_Tag *current_tag = find_XML_tag_in_childs(document, "dependencies");

    if(!current_tag)
    {
        printf("dependencies not found\n");
        return 0;
    }

    print_string(current_tag->name);

    return 0;
}
*/
