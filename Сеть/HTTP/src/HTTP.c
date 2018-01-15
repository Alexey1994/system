#include "HTTP.h"
#include "HTTP head parser/HTTP head parser.h"


static Byte get_HTTP_byte(HTTP *source)
{
    Byte byte=source->input_stream->head;

    source->length_data--;
    get_stream_byte(source->input_stream);

    return byte;
}


static char end_HTTP_data(HTTP *source)
{
    if(!source->length_data)
        return 1;

    return 0;
}


static String* create_GET_header(char *url)
{
    String *header = create_string(2);

    push_in_string(header, 'G');
    push_in_string(header, 'E');
    push_in_string(header, 'T');
    push_in_string(header, ' ');

    for(; *url; ++url)
        push_in_string(header, *url);

    push_in_string(header, 'H');
    push_in_string(header, 'T');
    push_in_string(header, 'T');
    push_in_string(header, 'P');
    push_in_string(header, '1');
    push_in_string(header, '.');
    push_in_string(header, '1');
    push_in_string(header, '\r');
    push_in_string(header, '\n');

    push_in_string(header, '\r');
    push_in_string(header, '\n');

    return header;
}


Stream *create_HTTP_stream(Stream *input_stream, char *url)
{
    Stream *http_stream;

    HTTP *source = new(HTTP);

    source->input_stream      = input_stream;
    source->end_of_data       = 0;
    source->count_to_end_head = 0;

    source->Access_Control_Allow_Origin = 0;
    source->Accept_Patch                = 0;
    source->Accept_Ranges               = 0;
    source->Age                         = 0;
    source->Allow                       = 0;
    source->Alt_Svc                     = 0;
    source->Cache_Control               = 0;
    source->Connection                  = 0;
    source->Content_Disposition         = 0;
    source->Content_Encoding            = 0;
    source->Content_Language            = 0;
    source->Content_Length              = 0;
    source->Content_Location            = 0;
    source->Content_MD5                 = 0;
    source->Content_Range               = 0;
    source->Content_Type                = 0;
    source->Date                        = 0;
    source->ETag                        = 0;
    source->Expires                     = 0;
    source->Last_Modified               = 0;
    source->Link                        = 0;
    source->Location                    = 0;
    source->P3P                         = 0;
    source->Pragma                      = 0;
    source->Proxy_Authenticate          = 0;
    source->Public_Key_Pins             = 0;
    source->Refresh                     = 0;
    source->Retry_After                 = 0;
    source->Server                      = 0;
    source->Set_Cookie                  = 0;
    source->Status                      = 0;
    source->Strict_Transport_Security   = 0;
    source->Trailer                     = 0;
    source->Transfer_Encoding           = 0;
    source->TSV                         = 0;
    source->Upgrade                     = 0;
    source->Vary                        = 0;
    source->Via                         = 0;
    source->Warning                     = 0;
    source->WWW_Authenticate            = 0;
    source->X_Frame_Options             = 0;

    source->X_XSS_Protection            = 0;
    source->Content_Security_Policy     = 0;
    source->X_Content_Type_Options      = 0;
    source->X_Powered_By                = 0;
    source->X_UA_Compatible             = 0;
    source->X_Content_Duration          = 0;
    source->Upgrade_Insecure_Requests   = 0;
    source->X_Request_ID                = 0;

    if(!read_HTTP_head(source))
    {
        print_error("");
        return 0;
    }

    http_stream = create_stream(source, get_HTTP_byte, end_HTTP_data);

    source->length_data = source->Content_Length+1;

    return http_stream;
}


int get_HTTP_length_from_stream(Stream *stream)
{
    Stream *HTTP_stream = create_HTTP_stream(stream, "");
    HTTP   *source      = HTTP_stream->source;

    //destroy_stream(HTTP_stream);

    return source->Content_Length;
}
