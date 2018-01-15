#ifndef XOR_MAPPED_ADDRESS_STUN_ATTRIBUTE_H_INCLUDED
#define XOR_MAPPED_ADDRESS_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_XOR_MAPPED_ADDRESS_attribute(Byte *attribute, int length);
void read_XOR_MAPPED_ADDRESS_attribute(STUN_Attributes *attributes, Byte *attribute, int length);



#endif // XOR_MAPPED_ADDRESS_STUN_ATTRIBUTE_H_INCLUDED
