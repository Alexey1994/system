#define __WIN32__
#include <system/devices/graphics/graphics.h>
#include "figures.h"
//#include <human interface/graphics/2D/events/events.h>


void draw(Canvas *canvas)
{
    static Rectangle rectangle  = {10, 10, 100, 100};
    N_32 i;

    clear_canvas(canvas);

    //move_if_moved(on_rectangle, &rectangle, get_rectangle_x, get_rectangle_y, set_rectangle_x, set_rectangle_y);
    draw_rectangle(canvas, &rectangle);
/*
    for(i=0; i<100; ++i)
    {
        rectangle.x = i*10;
        rectangle.y = i*10;
        draw_rectangle(&current_canvas, &rectangle);
    }*/
}


int main()
{
    initialize_graphics(1440, 900, 60, draw);

    for(;;){}

    return 0;
}

