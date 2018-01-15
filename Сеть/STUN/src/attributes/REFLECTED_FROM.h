#ifndef REFLECTED_FROM_STUN_ATTRIBUTE_H_INCLUDED
#define REFLECTED_FROM_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_REFLECTED_FROM_attribute(Byte *attribute, int length);
void read_REFLECTED_FROM_attribute(STUN_Attributes *attributes, Byte *attribute, int length);



#endif // REFLECTED_FROM_STUN_ATTRIBUTE_H_INCLUDED
