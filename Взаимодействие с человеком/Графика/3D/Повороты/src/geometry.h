#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED


#include "extends.h"


typedef struct
{
    float x;
    float y;
    float z;
}
Vector;


typedef Vector Point;


typedef struct
{
    Point M0;
    Point M1;
}
Line;


typedef struct
{
    Point P1;
    Point P2;
    Point P3;
}
Triangle;


void build_vector_by_points(Point *start, Point *end, Vector *result);

void cross_product(Vector *a, Vector *b, Vector *result_normal);
float dot_product(Vector *a, Vector *b);
Boolean line_intersect_triangle(Line *line, Triangle *triangle);

#endif // GEOMETRY_H_INCLUDED
