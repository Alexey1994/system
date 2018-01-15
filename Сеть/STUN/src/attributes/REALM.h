#ifndef REALM_STUN_ATTRIBUTE_H_INCLUDED
#define REALM_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_REALM_attribute(Byte *attribute, int length);
void read_REALM_attribute(STUN_Attributes *attributes, Byte *attribute, int length);



#endif // REALM_STUN_ATTRIBUTE_H_INCLUDED
