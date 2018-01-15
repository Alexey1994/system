#ifndef VECTOR_H_INCLUDED
#define VECTOR_H_INCLUDED


#include <mathematic/geometry/point/point.h>


typedef Point    Vector;
typedef Point_2D Vector_2D;
typedef Point_3D Vector_3D;


procedure         build_vector_by_points (Vector *vector, Point *p1, Point *p2);
function  R_32    vector_length          (Vector *vector);
function  R_32    dot_product            (Vector *a, Vector *b);
function  Vector* cross_product          (Vector *a, Vector *b);
procedure         normalize_vector       (Vector *vector);


#include "vector.c"

#endif // VECTOR_H_INCLUDED
