#ifndef STUN_MAPPED_ADDRESS_ATTRIBUTE_STUN_ATTRIBUTE_H_INCLUDED
#define STUN_MAPPED_ADDRESS_ATTRIBUTE_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_MAPPED_ADDRESS_attribute(Byte *attribute, int length);
void read_MAPPED_ADDRESS_attribute(STUN_Attributes *attributes, Byte *attribute, int length);


#endif // STUN_MAPPED_ADDRESS_ATTRIBUTE_STUN_ATTRIBUTE_H_INCLUDED
