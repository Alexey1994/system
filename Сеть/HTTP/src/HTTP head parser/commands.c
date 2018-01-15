#include "commands.h"
#include "../HTTP.h"


static Boolean skip_http_head_spaces(Parser *parser)
{
    skip_spaces(parser);

    if(parser->input_stream->head!=':')
    {
        print_error("expected : in HTTP head\n");
        goto error;
    }

    get_stream_byte(parser->input_stream);
    skip_spaces(parser);

    return 1;

error:
    return 0;
}


static String* get_http_head_value(Parser *parser)
{
    String *value=create_string(2);

    if(!skip_http_head_spaces(parser))
        goto error;

    while(parser->input_stream->head!='\r')
    {
        push_in_string(value, parser->input_stream->head);
        get_stream_byte(parser->input_stream);
    }

    skip_spaces(parser);

    return value;

error:
    destroy_string(value);
    return 0;
}


Boolean parse_http_head_Access_Control_Allow_Origin(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Access_Control_Allow_Origin=get_http_head_value(parser);

    if(!http->Access_Control_Allow_Origin)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Accept_Patch(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Accept_Patch=get_http_head_value(parser);

    if(!http->Accept_Patch)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Accept_Ranges(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Accept_Ranges=get_http_head_value(parser);

    if(!http->Accept_Ranges)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Age(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Age=get_http_head_value(parser);

    if(!http->Age)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Allow(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Allow=get_http_head_value(parser);

    if(!http->Allow)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Alt_Svc(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Alt_Svc=get_http_head_value(parser);

    if(!http->Alt_Svc)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Cache_Control(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Cache_Control=get_http_head_value(parser);

    if(!http->Cache_Control)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Connection(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Connection=get_http_head_value(parser);

    if(!http->Connection)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Content_Disposition(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Content_Disposition=get_http_head_value(parser);

    if(!http->Content_Disposition)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Content_Encoding(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Content_Encoding=get_http_head_value(parser);

    if(!http->Content_Encoding)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Content_Language(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Content_Language=get_http_head_value(parser);

    if(!http->Content_Language)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Content_Length(Parser *parser)
{
    HTTP *http=parser->language_parser;

    if(!skip_http_head_spaces(parser))
        goto error;

    http->Content_Length=get_text_stream_uint(parser->input_stream);
    skip_spaces(parser);

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Content_Location(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Content_Location=get_http_head_value(parser);

    if(!http->Content_Location)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Content_MD5(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Content_MD5=get_http_head_value(parser);

    if(!http->Content_MD5)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Content_Range(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Content_Range=get_http_head_value(parser);

    if(!http->Content_Range)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Content_Type(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Content_Type=get_http_head_value(parser);

    if(!http->Content_Type)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Date(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Date=get_http_head_value(parser);

    if(!http->Date)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_ETag(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->ETag=get_http_head_value(parser);

    if(!http->ETag)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Expires(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Expires=get_http_head_value(parser);

    if(!http->Expires)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Last_Modified(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Last_Modified=get_http_head_value(parser);

    if(!http->Last_Modified)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Link(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Link=get_http_head_value(parser);

    if(!http->Link)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Location(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Location=get_http_head_value(parser);

    if(!http->Location)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_P3P(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->P3P=get_http_head_value(parser);

    if(!http->P3P)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Pragma(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Pragma=get_http_head_value(parser);

    if(!http->Pragma)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Proxy_Authenticate(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Proxy_Authenticate=get_http_head_value(parser);

    if(!http->Proxy_Authenticate)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Public_Key_Pins(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Public_Key_Pins=get_http_head_value(parser);

    if(!http->Public_Key_Pins)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Refresh(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Refresh=get_http_head_value(parser);

    if(!http->Refresh)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Retry_After(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Retry_After=get_http_head_value(parser);

    if(!http->Retry_After)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Server(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Server=get_http_head_value(parser);

    if(!http->Server)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Set_Cookie(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Set_Cookie=get_http_head_value(parser);

    if(!http->Set_Cookie)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Status(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Status=get_http_head_value(parser);

    if(!http->Status)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Strict_Transport_Security(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Strict_Transport_Security=get_http_head_value(parser);

    if(!http->Strict_Transport_Security)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Trailer(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Trailer=get_http_head_value(parser);

    if(!http->Trailer)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Transfer_Encoding(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Transfer_Encoding=get_http_head_value(parser);

    if(!http->Transfer_Encoding)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_TSV(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->TSV=get_http_head_value(parser);

    if(!http->TSV)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Upgrade(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Upgrade=get_http_head_value(parser);

    if(!http->Upgrade)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Vary(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Vary=get_http_head_value(parser);

    if(!http->Vary)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Via(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Via=get_http_head_value(parser);

    if(!http->Via)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Warning(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Warning=get_http_head_value(parser);

    if(!http->Warning)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_WWW_Authenticate(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->WWW_Authenticate=get_http_head_value(parser);

    if(!http->WWW_Authenticate)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_X_Frame_Options(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->X_Frame_Options=get_http_head_value(parser);

    if(!http->X_Frame_Options)
        goto error;

    return 1;

error:
    return 0;
}
////////////////////////////Common non-standard response fields//////////////////////////////////////////////////////////

Boolean parse_http_head_X_XSS_Protection(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->X_XSS_Protection=get_http_head_value(parser);

    if(!http->X_XSS_Protection)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Content_Security_Policy(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Content_Security_Policy=get_http_head_value(parser);

    if(!http->Content_Security_Policy)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_X_Content_Type_Options(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->X_Content_Type_Options=get_http_head_value(parser);

    if(!http->X_Content_Type_Options)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_X_Powered_By(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->X_Powered_By=get_http_head_value(parser);

    if(!http->X_Powered_By)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_X_UA_Compatible(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->X_UA_Compatible=get_http_head_value(parser);

    if(!http->X_UA_Compatible)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_X_Content_Duration(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->X_Content_Duration=get_http_head_value(parser);

    if(!http->X_Content_Duration)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_Upgrade_Insecure_Requests(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->Upgrade_Insecure_Requests=get_http_head_value(parser);

    if(!http->Upgrade_Insecure_Requests)
        goto error;

    return 1;

error:
    return 0;
}


Boolean parse_http_head_X_Request_ID(Parser *parser)
{
    HTTP *http=parser->language_parser;

    http->X_Request_ID=get_http_head_value(parser);

    if(!http->X_Request_ID)
        goto error;

    return 1;

error:
    return 0;
}
