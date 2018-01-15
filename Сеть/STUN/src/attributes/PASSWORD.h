#ifndef PASSWORD_STUN_ATTRIBUTE_H_INCLUDED
#define PASSWORD_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_PASSWORD_attribute(Byte *attribute, int length);
void read_PASSWORD_attribute(STUN_Attributes *attributes, Byte *attribute, int length);



#endif // PASSWORD_STUN_ATTRIBUTE_H_INCLUDED
