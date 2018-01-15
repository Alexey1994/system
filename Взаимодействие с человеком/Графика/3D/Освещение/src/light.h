#ifndef LIGHT_H_INCLUDED
#define LIGHT_H_INCLUDED


#include <libs/graphics/geometry/vector/vector.h>


extern Vector light;


void initialize_light   ();
void deinitialize_light ();

void set_light_position (float x, float y, float z);
void rotate_light       (float angle, Vector *vector);


#include "light.c"

#endif // LIGHT_H_INCLUDED
