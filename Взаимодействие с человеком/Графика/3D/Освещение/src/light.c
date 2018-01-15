#include <math.h>


Vector light;


void initialize_light()
{
    initialize_3D_point(&light, 0, 1, 1);
}


void deinitialize_light()
{
    deinitialize_point(&light);
}


void set_light_position(float x, float y, float z)
{
    light.coords[0] = x;
    light.coords[1] = y;
    light.coords[2] = z;
}


void rotate_light(float angle, Vector *vector)
{

}
