#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED


//#include <libs/graphics/geometry/transformation/transformation.h>
#include <libs/graphics/canvas/canvas.h>


typedef struct
{
    float *coords;
    int    length;
}
Point;


void   initialize_point            (Point *point, int length);
void   initialize_3D_point         (Point *point, float x, float y, float z);
void   initialize_point_from_point (Point *p1, Point *p2);
void   deinitialize_point          (Point *point);

Point* create_point                (int length);
Point* create_3D_point             (float x, float y, float z);
void   destroy_point               (Point *point);

void   copy_point                  (Point *result, Point *source);
void   rasterize_point             (Point *point, Canvas *canvas);


#include "point.c"

#endif // POINT_H_INCLUDED
