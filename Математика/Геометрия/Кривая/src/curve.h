#ifndef CURVE_H_INCLUDED
#define CURVE_H_INCLUDED


#include <human interface/graphics/canvas/canvas.h>
#include <data structures/buffer/buffer.h>
#include <output/output.h>
//#include <data structures/array/array.h>
#include <mathematic/combinatorics/combinatorics.h>
#include <mathematic/geometry/point/point.h>


typedef struct
{
    N_32   length;
    Buffer points;
    Output points_output;
}
Curve;


procedure initialize_curve   (Curve *curve);
procedure deinitialize_curve (Curve *curve);


#include "curve.c"

#endif // CURVE_H_INCLUDED
