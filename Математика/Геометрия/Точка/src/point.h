#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED


#include <extends/extends.h>
#include <human interface/graphics/canvas/canvas.h>


typedef struct
{
    //float *coords;
    //int    length;
    N_32 length;
    R_32 coords[];
}
Point;


typedef struct
{
	N_32 length;
	R_32 x;
	R_32 y;
}
Point_2D;


typedef struct
{
	N_32 length;
	R_32 x;
	R_32 y;
	R_32 z;
}
Point_3D;


//#define initialize_point(point, length) { point = alloca(sizeof(Point) + length * sizeof(R_32)); point->length = length; }
//#define initialize_point(point, length) point = alloca(sizeof(Point) + length * sizeof(R_32))

procedure        initialize_point            (Point *point, N_32 length);
procedure        initialize_point_2D         (Point_2D *point, R_32 x, R_32 y);
procedure        initialize_point_3D         (Point_3D *point, R_32 x, R_32 y, R_32 z);
procedure        initialize_point_from_point (Point *p1, Point *p2);
/*
function  Point* create_point                (N_32 length);
function  Point* create_3D_point             (R_32 x, R_32 y, R_32 z);
procedure        destroy_point               (Point *point);
*/
procedure        copy_point                  (Point *result, Point *source);
procedure        draw_point                  (Point *point, Canvas *canvas);


#include "point.c"

#endif // POINT_H_INCLUDED
