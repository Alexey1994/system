#ifndef POINT_H_INCLUDED
#define POINT_H_INCLUDED


#include <extends/extends.h>
#include <human interface/graphics/canvas/canvas.h>


typedef struct
{
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


procedure        initialize_point            (Point *point, N_32 length);
procedure        initialize_point_2D         (Point_2D *point, R_32 x, R_32 y);
procedure        initialize_point_3D         (Point_3D *point, R_32 x, R_32 y, R_32 z);
procedure        initialize_point_from_point (Point *p1, Point *p2);

procedure        copy_point                  (Point *result, Point *source);
procedure        draw_point                  (Point *point, Canvas *canvas);


#include "point.c"

#endif // POINT_H_INCLUDED
