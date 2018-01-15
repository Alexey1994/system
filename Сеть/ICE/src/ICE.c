#include "ICE.h"
#include <libs/network/info/network info.h>


void add_ICE_candidate_in_SDP_message(SDP_Message *message, long long int priority, char *host, unsigned short port, char *type)
{
    String *candidate_text = create_string(10);
    Stream *candidate_stream = create_output_stream(candidate_text, push_in_string);

    write_int_in_text_output_stream(candidate_stream, message->a->length);
    put_stream_byte(candidate_stream, ' ');

    write_int_in_text_output_stream(candidate_stream, 1);
    put_stream_byte(candidate_stream, ' ');

    write_text_in_output_stream(candidate_stream, "UDP ");

    write_int_in_text_output_stream(candidate_stream, priority);
    put_stream_byte(candidate_stream, ' ');

    write_text_in_output_stream(candidate_stream, host);
    put_stream_byte(candidate_stream, ' ');

    write_int_in_text_output_stream(candidate_stream, port);
    put_stream_byte(candidate_stream, ' ');

    write_text_in_output_stream(candidate_stream, "typ ");
    write_text_in_output_stream(candidate_stream, type);

    //copy_char_array_to_string(candidate_text, "1 1 UDP 2130706431 10.0.1.1 8998 typ host");
    add_SDP_attribute_a(message, "candidate", candidate_text);

    destroy_stream(candidate_stream);
}


SDP_Message* get_ICE_SDP_message(char *STUN_host, unsigned short STUN_port)
{
    char            computer_host[16];
    char            mapped_host[16];
    unsigned short  mapped_port;

    SDP_Message    *message = create_SDP_message();
    String         *value   = create_string(10);

    get_IPv4_host_address(computer_host);
    get_STUN_MAPPED_ADDRESS(STUN_host, STUN_port, mapped_host, &mapped_port);

    set_SDP_attribute_v(message, 0);
    set_SDP_attribute_o(message, "lex", 1234, 0, 4, computer_host);
    set_SDP_attribute_s(message, "Cisco SDP 0");
    add_ICE_candidate_in_SDP_message(message, 2130706431, computer_host, mapped_port, "host");
    add_ICE_candidate_in_SDP_message(message, 1694498815, mapped_host, mapped_port, "srflx");

    return message;
}
