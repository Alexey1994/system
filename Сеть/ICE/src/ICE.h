#ifndef ICE_H_INCLUDED
#define ICE_H_INCLUDED


#include <libs/network/STUN/STUN.h>
#include <libs/network/SDP/SDP.h>


SDP_Message* get_ICE_SDP_message(char *STUN_host, unsigned short STUN_port);


#endif // ICE_H_INCLUDED
