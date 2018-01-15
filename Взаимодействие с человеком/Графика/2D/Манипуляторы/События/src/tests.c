#include <windows.h>
#include <system/devices/graphics/graphics.h>
#include "events.h"


void draw(Canvas *canvas)
{
    static Rectangle a = {100, 100, 100, 100};
    static Rectangle b = {400, 200, 100, 100};

    if(clicked(&on_rectangle, &b))
        printf("Ok1\n");

    if(move_if_moved(&on_rectangle, &a, &get_rectangle_x, &get_rectangle_y, &set_rectangle_x, &set_rectangle_y))
        printf("move\n");
/*
    if(pressed(&on_rectangle, &a))
        glColor3f(0.9, 0.9, 0.9);
    else if(is_hover(&on_rectangle, &a))
        glColor3f(0.1, 0.1, 0.1);
    else
        glColor3f(0, 0, 0);

    draw_rectangle(canvas, &a);

    if(is_hover(&on_rectangle, &b))
        glColor3f(0, 0.3, 0);
    else
        glColor3f(0, 0, 0);
*/
    clear_canvas(canvas);
    draw_rectangle(canvas, &a);
    draw_rectangle(canvas, &b);
}


int main()
{
    unsigned int width             = 1440;
    unsigned int height            = 900;
    unsigned int frames_per_second = 60;

    initialize_graphics(width, height, frames_per_second, draw);
    //start_mouse_coords_update(width, height);

    for(;;)
    {
        //if(pressed_key(VK_ESCAPE))
        //    break;
    }

    return 0;
}
