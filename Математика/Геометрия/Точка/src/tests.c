#include <windows.h>
#include "point.h"
#include <system/devices/graphics/graphics.h>


procedure draw(Canvas *canvas)
{
    Point_2D point;

    initialize_point_2D(&point, 30, 30);
    draw_point(&point, canvas);
}


int main()
{
    Point_3D point;
    //Point point;

    //printf("%d", sizeof(point));
    initialize_point_3D(&point, 1, 2, 3);
    //printf("%d (%f, %f, %f)\n", point.length, point.x, point.y, point.z);
    initialize_graphics(1440, 900, 60, &draw);

    for(;;);

    return 0;
}
