#ifndef POLYGON_H_INCLUDED
#define POLYGON_H_INCLUDED


#include <libs/graphics/geometry/transformation/transformation.h>


typedef Point* Triangle[3];
typedef Point* Quad[4];


void      initialize_triangle   (Triangle triangle, Point *p1, Point *p2, Point *p3);
void      deinitialize_triangle (Triangle triangle);

Triangle* create_triangle       (Point *p1, Point *p2, Point *p3);
void      destroy_triangle      (Triangle *triangle);

void      initialize_quad       (Quad quad, Point *p1, Point *p2, Point *p3, Point *p4);
void      deinitialize_quad     (Quad quad);

Quad*     create_quad           (Point *p1, Point *p2, Point *p3, Point *p4);
void      destroy_quad          (Quad *quad);

void      draw_triangle         (Triangle triangle);
Triangle* rotate_triangle       (Triangle triangle, Rotate *rotate);
Triangle* scale_triangle        (Triangle triangle, Scale *scale);
Triangle* translate_triangle    (Triangle triangle, Translate *translate);


#include "polygon.c"

#endif // POLYGON_H_INCLUDED
