#ifndef FINGERPRINT_STUN_ATTRIBUTE_H_INCLUDED
#define FINGERPRINT_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_FINGERPRINT_attribute(Byte *attribute, int length);
void read_FINGERPRINT_attribute(STUN_Attributes *attributes, Byte *attribute, int length);


#endif // FINGERPRINT_STUN_ATTRIBUTE_H_INCLUDED
