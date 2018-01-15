#include <windows.h>
#include "curve.h"
#include <system/devices/graphics/graphics.h>
#include <system/devices/mouse/mouse.h>


Curve    curve;
Array    points;
Point_2D point1;
Point_2D point2;
Point_2D point3;
Point_2D point4;
Point_2D point5;


procedure draw(Canvas *canvas)
{
    clear_canvas(canvas);
    //initialize_point_2D(&point2, get_mouse_coord_x(), get_mouse_coord_y());
    draw_curve(canvas, &curve);
}


function N_32 main()
{
    initialize_array(&points, 2, 0);

    initialize_point_2D(&point1, 0, 0);
    add_in_array(&points, &point1);

    initialize_point_2D(&point2, 200, 200);
    add_in_array(&points, &point2);

    initialize_point_2D(&point3, 400, 0);
    add_in_array(&points, &point3);

    initialize_point_2D(&point4, 500, 200);
    add_in_array(&points, &point4);

    initialize_point_2D(&point5, 1000, 0);
    add_in_array(&points, &point5);

    initialize_curve(&curve, &points);

    initialize_graphics(1440, 900, 60, &draw);

    for(;;);

    return 0;
}
