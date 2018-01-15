#ifndef USERNAME_STUN_ATTRIBUTE_H_INCLUDED
#define USERNAME_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_USERNAME_attribute(Byte *attribute, int length);
void read_USERNAME_attribute(STUN_Attributes *attributes, Byte *attribute, int length);



#endif // USERNAME_STUN_ATTRIBUTE_H_INCLUDED
