/*
#include <stdio.h>
#include <stdlib.h>

#include "SDP.h"

int main()
{
    SDP_Message *message       = create_SDP_message();
    String      *value         = create_string(10);
    String      *buffer        = create_string(10);
    Stream      *output_stream = create_output_stream(buffer, push_in_string);

    set_SDP_attribute_v(message, 0);
    set_SDP_attribute_o(message, "lex", 1234, 0, 4, "vk.com");
    set_SDP_attribute_s(message, "Cisco SDP 0");

    copy_char_array_to_string(value, "1 1 UDP 2130706431 10.0.1.1 8998 typ host");
    add_SDP_attribute_a(message, "candidate", value);

    get_SDP_text(message, output_stream);

    print_string(buffer);

    return 0;
}
*/
