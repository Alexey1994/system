#ifndef SDP_H_INCLUDED
#define SDP_H_INCLUDED


#include <libs/data structures/string/string.h>
#include <libs/extends/extends.h>
#include <libs/stream/stream.h>


typedef struct
{
    char   *name;
    String *value;
}
SDP_Attribute;


typedef struct
{
    struct
    {
        int version;
    }v;

    struct
    {
        char          *user_name;
        long long int  session_ID;
        long long int  session_version;
        Byte           ip_address_type;
        char          *host;
    }o;

    struct
    {
        char *session_name;
    }s;

    Array *a;
}
SDP_Message;


SDP_Message* create_SDP_Message();
void         destroy_SDP_Message(SDP_Message *message);

void         set_SDP_attribute_v(SDP_Message *message, int version);

void         set_SDP_attribute_o(SDP_Message   *message,
                                 char          *user_name,
                                 long long int  session_ID,
                                 long long int  session_version,
                                 Byte           ip_address_type,
                                 char          *host);

void         set_SDP_attribute_s(SDP_Message *message, char *session_name);

void         add_SDP_attribute_a(SDP_Message *message, char *name, String *value);

void         get_SDP_text(SDP_Message *message, Stream *output_stream);


#endif // SDP_H_INCLUDED
