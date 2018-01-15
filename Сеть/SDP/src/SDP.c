#include "SDP.h"


SDP_Message* create_SDP_message()
{
    SDP_Message *message = new(SDP_Message);

    message->a = create_array(1, destroy_string);

    return message;
}


void destroy_SDP_message(SDP_Message *message)
{
    free(message);
}


SDP_Attribute* create_SDP_Attribute()
{
    SDP_Attribute *attribute = new(SDP_Attribute);

    return attribute;
}


void destroy_SDP_Attribute(SDP_Attribute *attribute)
{
    free(attribute);
}


void set_SDP_attribute_v(SDP_Message *message, int version)
{
    message->v.version = version;
}


void set_SDP_attribute_o(SDP_Message   *message,
                         char          *user_name,
                         long long int  session_ID,
                         long long int  session_version,
                         Byte           ip_address_type,
                         char          *host)
{
    message->o.user_name       = user_name;
    message->o.session_ID      = session_ID;
    message->o.session_version = session_version;
    message->o.ip_address_type = ip_address_type;
    message->o.host            = host;
}

void set_SDP_attribute_s(SDP_Message *message, char *session_name)
{
    message->s.session_name = session_name;
}


void add_SDP_attribute_a(SDP_Message *message, char *name, String *value)
{
    SDP_Attribute *attribute = create_SDP_Attribute();

    attribute->name  = name;
    attribute->value = value;

    push_in_array(message->a, attribute);
}


void get_SDP_text(SDP_Message *message, Stream *output_stream)
{
    int            i;
    SDP_Attribute *attribute;

    //String *string = create_string(10);
    //Stream *stream = create_output_stream(string, push_in_string);


    write_text_in_output_stream(output_stream, "v=");
    write_int_in_text_output_stream(output_stream, message->v.version);
    write_text_in_output_stream(output_stream, "\r\n");


    write_text_in_output_stream(output_stream, "o=");

    if(message->o.user_name)
        write_text_in_output_stream(output_stream, message->o.user_name);
    else
        put_stream_byte(output_stream, '-');

    put_stream_byte(output_stream, ' ');

    write_int_in_text_output_stream(output_stream, message->o.session_ID);
    put_stream_byte(output_stream, ' ');

    write_int_in_text_output_stream(output_stream, message->o.session_version);
    write_text_in_output_stream(output_stream, " IN ");

    switch(message->o.session_version)
    {
        case 4: write_text_in_output_stream(output_stream, "IP4 "); break;
        case 6: write_text_in_output_stream(output_stream, "IP6 "); break;
    }

    write_text_in_output_stream(output_stream, message->o.host);
    write_text_in_output_stream(output_stream, "\r\n");


    write_text_in_output_stream(output_stream, "s=");
    write_text_in_output_stream(output_stream, message->s.session_name);
    write_text_in_output_stream(output_stream, "\r\n");


    for(i=0; i<message->a->length; ++i)
    {
        attribute = message->a->data[i];

        write_text_in_output_stream(output_stream, "a=");
        write_text_in_output_stream(output_stream, attribute->name);
        put_stream_byte(output_stream, ':');

        write_text_in_output_stream(output_stream, attribute->value->begin);
        write_text_in_output_stream(output_stream, "\r\n");
    }
}
