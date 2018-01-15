#ifndef GEOMETRY_H_INCLUDED
#define GEOMETRY_H_INCLUDED


#include <libs/extends/extends.h>


typedef struct
{
    int   width;
    int   height;
    int   bytes_per_pixel;
    Byte *data;
}
Canvas;


Canvas* create_canvas(int width, int height, int bytes_per_pixel);
void destroy_canvas(Canvas *canvas);

void clear_canvas(Canvas *canvas);

int create_texture(Canvas *canvas);
Byte* get_pixel(Canvas *canvas, int x, int y);
void fill_contours(Canvas *canvas);


typedef struct
{
    float x;
    float y;
}
Point2D;


Point2D* create_points(int length);
void     destroy_points(Point2D *points);


typedef struct
{
    Point2D *points;
    int      length;

    float   *coefficients;
}
BezierCurve;


BezierCurve* create_Bezier_curve(Point2D *points, int length);
void destroy_Bezier_curve(BezierCurve *curve);

void draw_Bezier_curve(BezierCurve *curve);
void rasterize_Bezier_curve(BezierCurve *curve, Canvas *canvas);

void draw_line(float x1, float y1, float x2, float y2);
void rasterize_line(float x1, float y1, float x2, float y2, Canvas *canvas);


#include "geometry.c"

#endif // GEOMETRY_H_INCLUDED
