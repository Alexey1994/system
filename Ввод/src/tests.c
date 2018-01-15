//#include <stdio.h>
#include "input.h"


Byte* fopen( char * fname, char * modeopen );
int feof ( Byte * filestream );
int fgetc( Byte * filestream );

typedef struct
{
    Byte *data;
}
Source;

function Boolean is_end_source(Source *source)
{
    return *source->data == 0;
}


function Byte read_source_byte(Source *source)
{
    Byte byte;

    byte = *source->data;
    ++source->data;
    return byte;
}


function test_input_head()
{
    Input  input;
    Source source;

    source.data = "abcd";
    initialize_input(&input, &source, &read_source_byte, &is_end_source);

    printf("%c", input_head(&input));

    read_byte(&input);
    printf("%c", input_head(&input));

    read_byte(&input);
    printf("%c", input_head(&input));

    read_byte(&input);
    printf("%c", input_head(&input));

    read_byte(&input);
    printf("%c", input_head(&input));

    read_byte(&input);
    printf("%c", input_head(&input));
}


function test_read_array()
{
    Input  input;
    Source source;
    Byte   array[5] = {0};

    source.data = "abcd";
    initialize_input(&input, &source, &read_source_byte, &is_end_source);

    read_byte_array(&input, array, 4);
    printf("<%s>\n", array);
}


function test_end_of_input()
{
    Input  input;
    Byte  *file_source;

    file_source = fopen("text.txt", "rb");
    initialize_input(&input, file_source, &fgetc, &feof);

    printf("<");
    while(!end_of_input(&input))
    {
        printf("%c", input_head(&input));
        read_byte(&input);
    }
    printf(">");
}


function test_read_if_next()
{
    Input  input;
    Byte  *file_source;

    file_source = fopen("text.txt", "rb");
    initialize_input(&input, file_source, &fgetc, &feof);

    if(read_if_next(&input, "asdg"))
    	printf("readed\n");
    else
    	printf("not readed\n");

    if(read_if_next(&input, "asdg"))
    	printf("readed\n");
    else
    	printf("not readed\n");

    if(read_if_next(&input, "asdfg"))
    	printf("readed\n");
    else
    	printf("not readed\n");

    printf("<");
    while(!end_of_input(&input))
    {
    	printf("%c", input_head(&input));
    	read_byte(&input);
    }
    printf(">");
    printf(" buffer begin %d\n", input.buffer.begin_index);
}


function int main()
{
    //test_input_head();
    //test_end_of_input();
    //test_read_array();
    test_read_if_next();

/*
    FILE  *input_file;
    Input  input;

    input_file = fopen("input.txt", "rb");
    initialize_input(&input, input_file, fgetc, feof);

    //printf("read  N 32: %d\n", read_N_32(&input));

    if(read_if_next(&input, "asdg"))
    	printf("readed\n");
    else
    	printf("not readed\n");

    if(read_if_next(&input, "asdg"))
    	printf("readed\n");
    else
    	printf("not readed\n");

    if(read_if_next(&input, "asdfg"))
    	printf("readed\n");
    else
    	printf("not readed\n");

    while(!end_of_input(&input))
    {
    	printf("%c", input_head(&input));
    	read_byte(&input);
    	//printf("%c", read_character(&input));
    }*/

    return 0;
}
