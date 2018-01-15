#include "translates.h"
#include <GL/gl.h>
#include <math.h>


#define SPEED_UP 0.01
#define SPEED_DOWN 0.01
#define SPEED_LEFT 0.01
#define SPEED_RIGHT 0.01


void actor(float *x, float *y, float *z, float mouse_x, float mouse_y)
{
    if(pressed_key('S'))
    {
        *x -= SPEED_DOWN * sin(mouse_x * M_PI/180.0f);
        *z -= SPEED_DOWN * cos(mouse_x * M_PI/180.0f);
    }

    if(pressed_key('W'))
    {
        *x += SPEED_DOWN * sin(mouse_x * M_PI/180.0f);
        *z += SPEED_DOWN * cos(mouse_x * M_PI/180.0f);
    }

    if(pressed_key('D'))
    {
        *x += SPEED_LEFT * cos(-mouse_x * M_PI/180.0f);
        *z += SPEED_LEFT * sin(-mouse_x * M_PI/180.0f);
    }

    if(pressed_key('A'))
    {
        *x -= SPEED_LEFT * cos(-mouse_x * M_PI/180.0f);
        *z -= SPEED_LEFT * sin(-mouse_x * M_PI/180.0f);
    }

    glRotatef(-mouse_y, 1, 0, 0);
    glRotatef(-mouse_x, 0, 1, 0);
    glTranslatef(*x, -*y, *z);
}
