#ifndef SOURCE_ADDRESS_STUN_ATTRIBUTE_H_INCLUDED
#define SOURCE_ADDRESS_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_SOURCE_ADDRESS_attribute(Byte *attribute, int length);
void read_SOURCE_ADDRESS_attribute(STUN_Attributes *attributes, Byte *attribute, int length);



#endif // SOURCE_ADDRESS_STUN_ATTRIBUTE_H_INCLUDED
