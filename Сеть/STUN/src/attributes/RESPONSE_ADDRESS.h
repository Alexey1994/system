#ifndef RESPONSE_ADDRESS_STUN_ATTRIBUTE_H_INCLUDED
#define RESPONSE_ADDRESS_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_RESPONSE_ADDRESS_attribute(Byte *attribute, int length);
void read_RESPONSE_ADDRESS_attribute(STUN_Attributes *attributes, Byte *attribute, int length);


#endif // RESPONSE_ADDRESS_STUN_ATTRIBUTE_H_INCLUDED
