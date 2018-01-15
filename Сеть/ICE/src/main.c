
#include <stdio.h>
#include <stdlib.h>

#include "ICE.h"

int main()
{
    initialize_STUN();

    SDP_Message *message;

    String *buffer        = create_string(10);
    Stream *output_stream = create_output_stream(buffer, push_in_string);

    message = get_ICE_SDP_message("stun.ideasip.com", 3478);

    get_SDP_text(message, output_stream);
    destroy_stream(output_stream);

    print_string(buffer);

    return 0;
}

