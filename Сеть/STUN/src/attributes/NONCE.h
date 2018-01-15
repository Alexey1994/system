#ifndef NONCE_STUN_ATTRIBUTE_H_INCLUDED
#define NONCE_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_NONCE_attribute(Byte *attribute, int length);
void read_NONCE_attribute(STUN_Attributes *attributes, Byte *attribute, int length);


#endif // NONCE_STUN_ATTRIBUTE_H_INCLUDED
