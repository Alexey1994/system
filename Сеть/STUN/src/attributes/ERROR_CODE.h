#ifndef ERROR_CODE_STUN_ATTRIBUTE_H_INCLUDED
#define ERROR_CODE_STUN_ATTRIBUTE_H_INCLUDED


#include <libs/extends/extends.h>
#include "../STUN.h"


void print_ERROR_CODE_attribute(Byte *attribute, int length);
void read_ERROR_CODE_attribute(STUN_Attributes *attributes, Byte *attribute, int length);


#endif // ERROR_CODE_STUN_ATTRIBUTE_H_INCLUDED
