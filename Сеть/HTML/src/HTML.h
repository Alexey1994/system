#ifndef HTML_H_INCLUDED
#define HTML_H_INCLUDED


#include <libs/data structures/prefix tree/prefix tree.h>
#include <libs/data structures/array/array.h>
#include <libs/data structures/buffer/buffer.h>
#include <libs/input/input.h>
#include <libs/output/output.h>
//#include <libs/data structures/string/string.h>
//#include <libs/stream/stream.h>


typedef struct
{
    //String *name;
    //String *data;
    Buffer *name;
    Buffer *data;
}
Attribute;


typedef enum
{
    TEXT_DATA = 0x01,
    TAG       = 0x02
}
TagStructure;


typedef struct
{
    Boolean      is_once;
    //String     *name;
    Buffer      *name;
    Prefix_Tree *attributes;
    Array       *structure;
}
Tag;


void initialize_HTML_parser();
Tag* parse_HTML(Input *input);
void print_html(Tag *root_tag, Output *output);


#include "HTML.c"

#endif // HTML_H_INCLUDED
