#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED


#include <libs/graphics/geometry/point/point.h>


typedef Point Vector;


//Vector* build_vector_by_points (Point *p1, Point *p2);
void    build_vector_by_points (Vector *vector, Point *p1, Point *p2);
float   vector_length          (Vector *vector);
float   dot_product            (Vector *a, Vector *b);
Vector* cross_product          (Vector *a, Vector *b);
void    normalize_vector       (Vector *vector);


#include "vector.c"

#endif // VECTOR_H_INCLUDED
