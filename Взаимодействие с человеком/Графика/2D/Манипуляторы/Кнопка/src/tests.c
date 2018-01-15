#include <windows.h>
#include <system/devices/graphics/graphics.h>
#include <system/interfaces/files/files.h>
#include "button.h"


void draw(Canvas *canvas)
{
    static Boolean        once               =  1;
    static Raster_Font    font;
    static Button         button;
    Input                 font_input;

    if(once)
    {
        initialize_file_input(&font_input, "default.fnt");
        read_raster_font(&font, &font_input);
        deinitialize_input(&font_input);

        initialize_button(&button, canvas, 100, 100, 200, 100, &font, "Hello");

        button.on_click_arguments = "Click\n";
        button.run_on_click = &printf;

        once=0;
    }

    clear_canvas(canvas);
    refresh_button(&button);
}


int main()
{
    initialize_graphics(1440, 900, 60, draw);

    for(;;)
    {
        //if(pressed_key(VK_ESCAPE))
        //    break;
    }

    return 0;
}
