#ifndef VECTOR_FONT_H_INCLUDED
#define VECTOR_FONT_H_INCLUDED


#include <data structures/array/array.h>
#include <human interface/graphics/canvas/canvas.h>
//#include <mathematic/geometry/line/line.h>
#include <mathematic/geometry/curve/curve.h>


typedef struct
{
    Array *curves;

    Z_32 min_x;
    Z_32 min_y;
    Z_32 max_x;
    Z_32 max_y;
}
Vector_Glyph;


procedure               initialize_vector_glyph   (Vector_Glyph *glyph);
procedure               deinitialize_vector_glyph (Vector_Glyph *glyph);
function  Vector_Glyph* create_vector_glyph       ();
procedure               destroy_vector_glyph      (Vector_Glyph *glyph);

procedure               add_curve_in_vector_glyph (Vector_Glyph *glyph, Curve *curve);
procedure               rasterize_vector_glyph    (Vector_Glyph *glyph, Canvas *canvas);


#include "vector font.c"

#endif //VECTOR_FONT_H_INCLUDED
