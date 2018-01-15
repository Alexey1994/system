#include "HTTP head parser.h"
#include "commands.h"


static PrefixTree *http_head_keywords = 0;


static void init_http_head_keywords()
{
    http_head_keywords=create_prefix_tree();

    add_data_in_prefix_tree(http_head_keywords, "Access-Control-Allow-Origin", parse_http_head_Access_Control_Allow_Origin);
    add_data_in_prefix_tree(http_head_keywords, "Accept-Patch",                parse_http_head_Accept_Patch);
    add_data_in_prefix_tree(http_head_keywords, "Accept-Ranges",               parse_http_head_Accept_Ranges);
    add_data_in_prefix_tree(http_head_keywords, "Age",                         parse_http_head_Age);
    add_data_in_prefix_tree(http_head_keywords, "Allow",                       parse_http_head_Allow);
    add_data_in_prefix_tree(http_head_keywords, "Alt-Svc",                     parse_http_head_Alt_Svc);
    add_data_in_prefix_tree(http_head_keywords, "Cache-Control",               parse_http_head_Cache_Control);
    add_data_in_prefix_tree(http_head_keywords, "Connection",                  parse_http_head_Connection);
    add_data_in_prefix_tree(http_head_keywords, "Content-Disposition",         parse_http_head_Content_Disposition);
    add_data_in_prefix_tree(http_head_keywords, "Content-Encoding",            parse_http_head_Content_Encoding);
    add_data_in_prefix_tree(http_head_keywords, "Content-Language",            parse_http_head_Content_Language);
    add_data_in_prefix_tree(http_head_keywords, "Content-Length",              parse_http_head_Content_Length);
    add_data_in_prefix_tree(http_head_keywords, "Content-Location",            parse_http_head_Content_Location);
    add_data_in_prefix_tree(http_head_keywords, "Content-MD5",                 parse_http_head_Content_MD5);
    add_data_in_prefix_tree(http_head_keywords, "Content-Range",               parse_http_head_Content_Range);
    add_data_in_prefix_tree(http_head_keywords, "Content-Type",                parse_http_head_Content_Type);
    add_data_in_prefix_tree(http_head_keywords, "Date",                        parse_http_head_Date);
    add_data_in_prefix_tree(http_head_keywords, "ETag",                        parse_http_head_ETag);
    add_data_in_prefix_tree(http_head_keywords, "Etag",                        parse_http_head_ETag);
    add_data_in_prefix_tree(http_head_keywords, "Expires",                     parse_http_head_Expires);
    add_data_in_prefix_tree(http_head_keywords, "Last-Modified",               parse_http_head_Last_Modified);
    add_data_in_prefix_tree(http_head_keywords, "Link",                        parse_http_head_Link);
    add_data_in_prefix_tree(http_head_keywords, "Location",                    parse_http_head_Location);
    add_data_in_prefix_tree(http_head_keywords, "P3P",                         parse_http_head_P3P);
    add_data_in_prefix_tree(http_head_keywords, "Pragma",                      parse_http_head_Pragma);
    add_data_in_prefix_tree(http_head_keywords, "Proxy-Authenticate",          parse_http_head_Proxy_Authenticate);
    add_data_in_prefix_tree(http_head_keywords, "Public-Key-Pins",             parse_http_head_Public_Key_Pins);
    add_data_in_prefix_tree(http_head_keywords, "Refresh",                     parse_http_head_Refresh);
    add_data_in_prefix_tree(http_head_keywords, "Retry-After",                 parse_http_head_Retry_After);
    add_data_in_prefix_tree(http_head_keywords, "Server",                      parse_http_head_Server);
    add_data_in_prefix_tree(http_head_keywords, "Set-Cookie",                  parse_http_head_Set_Cookie);
    add_data_in_prefix_tree(http_head_keywords, "Status",                      parse_http_head_Status);
    add_data_in_prefix_tree(http_head_keywords, "Strict-Transport-Security",   parse_http_head_Strict_Transport_Security);
    add_data_in_prefix_tree(http_head_keywords, "Trailer",                     parse_http_head_Trailer);
    add_data_in_prefix_tree(http_head_keywords, "Transfer-Encoding",           parse_http_head_Transfer_Encoding);
    add_data_in_prefix_tree(http_head_keywords, "TSV",                         parse_http_head_TSV);
    add_data_in_prefix_tree(http_head_keywords, "Upgrade",                     parse_http_head_Upgrade);
    add_data_in_prefix_tree(http_head_keywords, "Vary",                        parse_http_head_Vary);
    add_data_in_prefix_tree(http_head_keywords, "Via",                         parse_http_head_Via);
    add_data_in_prefix_tree(http_head_keywords, "Warning",                     parse_http_head_Warning);
    add_data_in_prefix_tree(http_head_keywords, "WWW-Authenticate",            parse_http_head_WWW_Authenticate);
    add_data_in_prefix_tree(http_head_keywords, "X-Frame-Options",             parse_http_head_X_Frame_Options);

    add_data_in_prefix_tree(http_head_keywords, "X-XSS-Protection",            parse_http_head_X_XSS_Protection);
    add_data_in_prefix_tree(http_head_keywords, "Content-Security-Policy",     parse_http_head_Content_Security_Policy);
    add_data_in_prefix_tree(http_head_keywords, "X-Content-Security-Policy",   parse_http_head_Content_Security_Policy);
    add_data_in_prefix_tree(http_head_keywords, "X-WebKit-CSP",                parse_http_head_Content_Security_Policy);
    add_data_in_prefix_tree(http_head_keywords, "X-Content-Type-Options",      parse_http_head_X_Content_Type_Options);
    add_data_in_prefix_tree(http_head_keywords, "X-Powered-By",                parse_http_head_X_Powered_By);
    add_data_in_prefix_tree(http_head_keywords, "X-UA-Compatible",             parse_http_head_X_UA_Compatible);
    add_data_in_prefix_tree(http_head_keywords, "X-Content-Duration",          parse_http_head_X_Content_Duration);
    add_data_in_prefix_tree(http_head_keywords, "Upgrade-Insecure-Requests",   parse_http_head_Upgrade_Insecure_Requests);
    add_data_in_prefix_tree(http_head_keywords, "X-Request-ID",                parse_http_head_X_Request_ID);
    add_data_in_prefix_tree(http_head_keywords, "X-Correlation-ID",            parse_http_head_X_Request_ID);
}


static Boolean get_HTTP_version(HTTP *source)
{
    if(read_if_on_stream_head(source->input_stream, "1.1"))
    {
        source->major_version=1;
        source->minor_version=1;
    }
    else
    {
        printf("HTTP version not supported\n");
        goto error;
    }

    return 1;

error:
    return 0;
}


static Boolean get_HTTP_status(HTTP *source)
{
    skip_text_stream(source->input_stream);

    source->status=get_text_stream_uint(source->input_stream);

    while(source->input_stream->head!='\n')
        get_stream_byte(source->input_stream);

    return 1;

error:
    return 0;
}


Boolean print_http_head_error(Parser *parser)
{
    print_error("keyword '");
    print_error(parser->word->begin);
    print_error("' in HTTP head not correct\n");

    return 0;
}


static Byte get_http_head_byte(HTTP *source)
{
    Byte byte = source->input_stream->head;

    switch(source->count_to_end_head)
    {
    case 0:
        if(byte=='\r')
            source->count_to_end_head++;
        else
            source->count_to_end_head=0;
        break;

    case 1:
        if(byte=='\n')
            source->count_to_end_head++;
        else
            source->count_to_end_head=0;
        break;

    case 2:
        if(byte=='\r')
            source->count_to_end_head++;
        else
            source->count_to_end_head=0;
        break;

    case 3:
        if(byte=='\n')
        {
            get_stream_byte(source->input_stream);
            source->end_of_data=1;
            return 0;
        }
        else
            source->count_to_end_head=0;
        break;
    }

    get_stream_byte(source->input_stream);

    return byte;
}


static Boolean end_of_http_head(HTTP *source)
{
    if(source->end_of_data)
        return 1;

    return 0;
}


static Boolean is_http_head_letter(Character c)
{
    if((c>='a' && c<='z') || (c>='A' && c<='Z') || c=='-')
        return 1;

    return 0;
}


Boolean read_HTTP_head(HTTP *source)
{
    Stream *head_parser_stream;

    if(!read_if_on_stream_head(source->input_stream, "HTTP/"))
    {
        print_error("head not contains HTTP\n");
        goto error;
    }

    if(!get_HTTP_version(source))
        goto error;

    if(!get_HTTP_status(source))
        goto error;

    head_parser_stream=create_stream(source, get_http_head_byte, end_of_http_head);

    if(!http_head_keywords)
        init_http_head_keywords();

    //if(!parse( create_parser(head_parser_stream, http_head_keywords, source, source, print_http_head_error, is_http_head_letter)) )
    if(!parse( create_parser(head_parser_stream, http_head_keywords, print_http_head_error, is_http_head_letter, source, 0)) )
        goto error;

    destroy_stream(head_parser_stream);

    return 1;

error:
    return 0;
}
