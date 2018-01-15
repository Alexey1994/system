
#include <stdio.h>
#include "HTTP.h"


Boolean dummy_end_of_data(Byte *source)
{
    return 0;
}


int main()
{
    char *http_head="GET /js/main.js HTTP/1.1\r\n"
                    "Host: iston.herokuapp.com\r\n"
                    "User-Agent: Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/53.0.2785.143 Safari/537.36\r\n"
                    "Connection: close\r\n"
                    "\r\n";
/*
    TCP_IP_connection *connection = create_TCP_IP_connection("iston.herokuapp.com", 80);

    if(!connection)
        return 0;

    open_TCP_IP(connection, http_head, strlen(http_head));

    Stream *input_stream = create_stream(connection, get_TCP_IP_byte, dummy_end_of_data);
    Stream *http_stream  = create_HTTP_stream(input_stream, "vk.com");

    if(!http_stream)
        return 0;

    HTTP   *http         = http_stream->source;

    //printf("HTTP version %d.%d\n", http->major_version, http->minor_version);
    //printf("status: %d", http->status);


    int i;
    FILE *f=fopen("a.html", "wb");

    for(i=0; i<http->Content_Length; i++)
    {
        fputc(http_stream->head, f);
        printf("%c", http_stream->head);
        get_stream_byte(http_stream);
    }*/

    String *s      = create_string(2);
    copy_char_array_to_string(s, http_head);

    Stream *stream = create_TCP_IP_stream(s, get_HTTP_length_from_stream, "builder-components.herokuapp.com", 80);

    while(!end_stream(stream))
    {
        printf("%c", stream->head);
        get_stream_byte(stream);
    }

    return 0;
}

