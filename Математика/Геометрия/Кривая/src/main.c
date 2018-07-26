#include <windows.h>
#include "curve.h"
#include <system/devices/graphics/graphics.h>
#include <system/devices/mouse/mouse.h>


Curve curve;


procedure draw(Canvas *canvas)
{
    clear_canvas(canvas);
    //initialize_point_2D(&point2, get_mouse_coord_x(), get_mouse_coord_y());
    draw_curve(canvas, &curve);
}


function N_32 main()
{
    Point point;

    initialize_curve(&curve);
        initialize_point_2D(&point, 0, 0);
        add_point_in_curve(&curve, &point);

        initialize_point_2D(&point, 100, 100);
        add_point_in_curve(&curve, &point);

        initialize_point_2D(&point, 200, 0);
        add_point_in_curve(&curve, &point);

    initialize_graphics(1440, 900, 60, &draw);

    for(;;);

    return 0;
}
