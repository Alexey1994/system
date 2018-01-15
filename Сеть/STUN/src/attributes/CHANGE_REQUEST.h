#ifndef CHANGE_REQUEST_STUN_ATTRIBUTE_H_INCLUDED
#define CHANGE_REQUEST_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_CHANGE_REQUEST_attribute(Byte *attribute, int length);
void read_CHANGE_REQUEST_attribute(STUN_Attributes *attributes, Byte *attribute, int length);


#endif // CHANGE_REQUEST_STUN_ATTRIBUTE_H_INCLUDED
