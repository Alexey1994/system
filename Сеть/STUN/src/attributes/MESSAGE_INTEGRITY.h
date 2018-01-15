#ifndef MESSAGE_INTEGRITY_STUN_ATTRIBUTE_H_INCLUDED
#define MESSAGE_INTEGRITY_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_MESSAGE_INTEGRITY_attribute(Byte *attribute, int length);
void read_MESSAGE_INTEGRITY_attribute(STUN_Attributes *attributes, Byte *attribute, int length);


#endif // MESSAGE_INTEGRITY_STUN_ATTRIBUTE_H_INCLUDED
