#ifndef TTF_H_INCLUDED
#define TTF_H_INCLUDED


#include <libs/stream/stream.h>
#include "geometry.h"


typedef struct
{
    BezierCurve **curves;
    int           number_of_curves;
}
Contour;


typedef struct
{
    Contour *contours;
    int      number_of_contours;

    short *coords;
    int    length;

    int width;
    int height;

    int min_x;
    int min_y;
    int max_x;
    int max_y;
}
Glyph;


typedef struct
{
    Glyph **glyphs;
}
TTF;


TTF* load_TTF(Stream *in);
void rasterize_glyph(Glyph *glyph, Canvas *canvas);


#include "TTF.c"

#endif // TTF_H_INCLUDED
