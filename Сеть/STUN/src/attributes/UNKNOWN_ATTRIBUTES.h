#ifndef UNKNOWN_ATTRIBUTES_STUN_ATTRIBUTE_H_INCLUDED
#define UNKNOWN_ATTRIBUTES_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_UNKNOWN_ATTRIBUTES_attribute(Byte *attribute, int length);
void read_UNKNOWN_ATTRIBUTES_attribute(STUN_Attributes *attributes, Byte *attribute, int length);



#endif // UNKNOWN_ATTRIBUTES_STUN_ATTRIBUTE_H_INCLUDED
