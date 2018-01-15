#ifndef CURVE_H_INCLUDED
#define CURVE_H_INCLUDED


#include <human interface/graphics/canvas/canvas.h>
#include <data structures/array/array.h>
#include <mathematic/combinatorics/combinatorics.h>
#include <mathematic/geometry/point/point.h>


typedef struct
{
    Array *points;
    N_32  *coefficients;
}
Curve;


procedure initialize_curve   (Curve *curve, Array *points);
procedure deinitialize_curve (Curve *curve);


#include "curve.c"

#endif // CURVE_H_INCLUDED
