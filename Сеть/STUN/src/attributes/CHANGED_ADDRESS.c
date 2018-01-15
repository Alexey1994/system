#include "CHANGED_ADDRESS.h"


void print_CHANGED_ADDRESS_attribute(Byte *attribute, int length)
{
    unsigned int   ip;
    unsigned short port;

    printf("\tCHANGED ADDRESS, %d bytes\n", length);

    printf("\t");

    switch(attribute[1])
    {
        case 1: printf("IPv4\n"); break;
        case 2: printf("IPv6\n"); break;
    }

    port = (attribute[2]<<8) + attribute[3];
    ip   = (attribute[4]<<24) + (attribute[5]<<16) + (attribute[6]<<8) + (attribute[7]);

    printf("\t%d.%d.%d.%d:%d\n", attribute[4], attribute[5], attribute[6], attribute[7], port);

    printf("\n");
}


void read_CHANGED_ADDRESS_attribute(STUN_Attributes *attributes, Byte *attribute, int length)
{

}
