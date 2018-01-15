#ifndef HTTP_H_INCLUDED
#define HTTP_H_INCLUDED

#include <libs/extends/extends.h>
#include <libs/TCP IP/TCP IP.h>
#include <libs/data structures/string/string.h>


typedef struct
{
    int     major_version;
    int     minor_version;
    int     status;

    String *Access_Control_Allow_Origin;
    String *Accept_Patch;
    String *Accept_Ranges;
    String *Age;
    String *Allow;
    String *Alt_Svc;
    String *Cache_Control;
    String *Connection;
    String *Content_Disposition;
    String *Content_Encoding;
    String *Content_Language;
    int     Content_Length;
    String *Content_Location;
    String *Content_MD5;
    String *Content_Range;
    String *Content_Type;
    String *Date;
    String *ETag;
    String *Expires;
    String *Last_Modified;
    String *Link;
    String *Location;
    String *P3P;
    String *Pragma;
    String *Proxy_Authenticate;
    String *Public_Key_Pins;
    String *Refresh;
    String *Retry_After;
    String *Server;
    String *Set_Cookie;
    String *Status;
    String *Strict_Transport_Security;
    String *Trailer;
    String *Transfer_Encoding;
    String *TSV;
    String *Upgrade;
    String *Vary;
    String *Via;
    String *Warning;
    String *WWW_Authenticate;
    String *X_Frame_Options;

    String *X_XSS_Protection;
    String *Content_Security_Policy;
    String *X_Content_Type_Options;
    String *X_Powered_By;
    String *X_UA_Compatible;
    String *X_Content_Duration;
    String *Upgrade_Insecure_Requests;
    String *X_Request_ID;

    int     length_data;
    Stream *input_stream;
    Boolean end_of_data;
    int     count_to_end_head;
}
HTTP;


Stream *create_HTTP_stream(Stream *input_stream, char *url);
int get_HTTP_length_from_stream(Stream *stream);


#endif // HTTP_H_INCLUDED
