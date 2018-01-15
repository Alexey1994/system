#ifndef XML_H_INCLUDED
#define XML_H_INCLUDED


#include <libs/data structures/prefix tree/prefix tree.h>
#include <libs/stream/stream.h>
#include <libs/data structures/string/string.h>


typedef struct
{
    String *name;
    String *data;
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
    //Boolean     is_once;
    String     *name;
    PrefixTree *attributes;
    Array      *structure;
}
XML_Tag;


void       initialize_XML_parser();
XML_Tag*   parse_XML(Stream *input_stream);

//Navigation
XML_Tag*   find_XML_tag_in_childs(XML_Tag *parent, char *tag_name);
Array*     find_all_XML_tags_in_childs(XML_Tag *parent, char *tag_name);
Attribute* get_XML_Tag_attribute(XML_Tag *tag, char *attribute_name);

void       print_formatted_XML(XML_Tag *root_tag, Stream *output_stream);
void       print_XML(XML_Tag *root_tag, Stream *output_stream);


#endif // XML_H_INCLUDED
