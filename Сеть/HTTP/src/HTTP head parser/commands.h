#ifndef HTTP_HEAD_PARSER_COMMANDS_H_INCLUDED
#define HTTP_HEAD_PARSER_COMMANDS_H_INCLUDED


#include <libs/parser/parser.h>

/*
Boolean parse_http_head_Content_Length(Parser *parser);
Boolean parse_http_head_Content_Type(Parser *parser);
Boolean parse_http_head_Server(Parser *parser);
Boolean parse_http_head_Date(Parser *parser);
Boolean parse_http_head_Connection(Parser *parser);
Boolean parse_http_head_X_Powered_By(Parser *parser);
Boolean parse_http_head_Set_Cookie(Parser *parser);
Boolean parse_http_head_Location(Parser *parser);
Boolean parse_http_head_Vary(Parser *parser);*/

Boolean parse_http_head_Access_Control_Allow_Origin(Parser *parser);
Boolean parse_http_head_Accept_Patch(Parser *parser);
Boolean parse_http_head_Accept_Ranges(Parser *parser);
Boolean parse_http_head_Age(Parser *parser);
Boolean parse_http_head_Allow(Parser *parser);
Boolean parse_http_head_Alt_Svc(Parser *parser);
Boolean parse_http_head_Cache_Control(Parser *parser);
Boolean parse_http_head_Connection(Parser *parser);
Boolean parse_http_head_Content_Disposition(Parser *parser);
Boolean parse_http_head_Content_Encoding(Parser *parser);
Boolean parse_http_head_Content_Language(Parser *parser);
Boolean parse_http_head_Content_Length(Parser *parser);
Boolean parse_http_head_Content_Location(Parser *parser);
Boolean parse_http_head_Content_MD5(Parser *parser);
Boolean parse_http_head_Content_Range(Parser *parser);
Boolean parse_http_head_Content_Type(Parser *parser);
Boolean parse_http_head_Date(Parser *parser);
Boolean parse_http_head_ETag(Parser *parser);
Boolean parse_http_head_Expires(Parser *parser);
Boolean parse_http_head_Last_Modified(Parser *parser);
Boolean parse_http_head_Link(Parser *parser);
Boolean parse_http_head_Location(Parser *parser);
Boolean parse_http_head_P3P(Parser *parser);
Boolean parse_http_head_Pragma(Parser *parser);
Boolean parse_http_head_Proxy_Authenticate(Parser *parser);
Boolean parse_http_head_Public_Key_Pins(Parser *parser);
Boolean parse_http_head_Refresh(Parser *parser);
Boolean parse_http_head_Retry_After(Parser *parser);
Boolean parse_http_head_Server(Parser *parser);
Boolean parse_http_head_Set_Cookie(Parser *parser);
Boolean parse_http_head_Status(Parser *parser);
Boolean parse_http_head_Strict_Transport_Security(Parser *parser);
Boolean parse_http_head_Trailer(Parser *parser);
Boolean parse_http_head_Transfer_Encoding(Parser *parser);
Boolean parse_http_head_TSV(Parser *parser);
Boolean parse_http_head_Upgrade(Parser *parser);
Boolean parse_http_head_Vary(Parser *parser);
Boolean parse_http_head_Via(Parser *parser);
Boolean parse_http_head_Warning(Parser *parser);
Boolean parse_http_head_WWW_Authenticate(Parser *parser);
Boolean parse_http_head_X_Frame_Options(Parser *parser);

Boolean parse_http_head_X_XSS_Protection(Parser *parser);
Boolean parse_http_head_Content_Security_Policy(Parser *parser);
Boolean parse_http_head_X_Content_Type_Options(Parser *parser);
Boolean parse_http_head_X_Powered_By(Parser *parser);
Boolean parse_http_head_X_UA_Compatible(Parser *parser);
Boolean parse_http_head_X_Content_Duration(Parser *parser);
Boolean parse_http_head_Upgrade_Insecure_Requests(Parser *parser);
Boolean parse_http_head_X_Request_ID(Parser *parser);


#endif // HTTP_HEAD_PARSER_COMMANDS_H_INCLUDED
