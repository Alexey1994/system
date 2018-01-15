#ifndef SOFTWARE_STUN_ATTRIBUTE_H_INCLUDED
#define SOFTWARE_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_SOFTWARE_attribute(Byte *attribute, int length);
void read_SOFTWARE_attribute(STUN_Attributes *attributes, Byte *attribute, int length);


#endif // SOFTWARE_STUN_ATTRIBUTE_H_INCLUDED
