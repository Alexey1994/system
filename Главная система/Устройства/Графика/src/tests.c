#include <x86 32 bit.h>
//#include <windows.h>

//#include <system/devices/mouse/mouse.h>
#include "graphics.h"


typedef struct
{
    N_32 x;
    N_32 y;
    N_32 width;
    N_32 height;
}
Rectangle;


procedure draw_rectangle(Rectangle *rectangle, Canvas *canvas)
{
    N_32  x;
    N_32  y;
    Byte *pixel;

    for(y=rectangle->y; y<rectangle->y + rectangle->height; ++y)
    {
        for(x=rectangle->x; x<rectangle->x + rectangle->width; ++x)
        {
            pixel = get_canvas_pixel(canvas, x, y);
            fill_canvas_pixel(canvas, pixel);
        }
    }
}


procedure draw_scene(Canvas *canvas)
{
    Rectangle rect;
    static N_32 x = 0;
    static N_32 y = 0;

    rect.x = 10 + x;//get_mouse_coord_x();
    rect.y = 10;//get_mouse_coord_y();
    rect.width = 100;
    rect.height = 100;
++x;
    clear_canvas(canvas);
    set_canvas_color(canvas, 255, 0, 0, 255);
    draw_rectangle(&rect, canvas);
}


N_32 main()
{
    initialize_graphics(1440, 900, 120, &draw_scene);

    return 0;
}
