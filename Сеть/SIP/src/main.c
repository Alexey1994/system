#include <stdio.h>
#include <stdlib.h>
#include <libs/data structures/string/string.h>
#include <libs/stream/stream.h>
#include <libs/network/SDP/SDP.h>


int main()
{
    String      *SDP_string  = create_string(10);
    Stream      *SDP_stream  = create_output_stream(SDP_string, push_in_string);

    Stream      *SIP_string  = create_string(10);
    Stream      *SIP_stream  = create_output_stream(SIP_string, push_in_string);

    SDP_Message *SDP_message = create_SDP_message();

    set_SDP_attribute_v(SDP_message, 0);
    set_SDP_attribute_o(SDP_message, "lex", 1234, 0, 4, "vk.com");
    set_SDP_attribute_s(SDP_message, "Cisco SDP 0");

    get_SDP_text(SDP_message, SDP_stream);


    write_text_in_output_stream(SIP_stream,
        "REGISTER sip:hotfoon.com SIP/2.0\r\n"
        "Via: SIP/2.0/UDP vk.com\r\n"
        "From: sip:alice@hotfoon.com\r\n"
        "To: sip:alice:queen@hotfoon.com\r\n"
        "Call-ID: 17320@hotfoon.com\r\n"
        "CSeq: 1 REGISTER\r\n"
        "Expires: 7200\r\n"
        "Contact: Alice\r\n"
        "Content-Length:");

    write_int_in_text_output_stream(SIP_stream, SDP_string->length);
    write_text_in_output_stream(SIP_stream, "\r\n\r\n");

    print_string(SIP_string);
    print_string(SDP_string);

    return 0;
}
