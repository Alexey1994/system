#include <stdio.h>
#include <GL/gl.h>
//#include "extends.h"
//#include "lib/graphics.h"
//#include "lib/input.h"
//#include "button.h"
//#include <libs/graphics/GUI/fonts/raster/font.h>
//#include <libs/graphics/GUI/components/button/button.h>
#include "program space.h"

/*
void draw()
{
    static Boolean  once               =  1;
    static Font    *font;
    static Button  *button;
    static Window  *window;
    Stream         *font_input_stream;

    if(once)
    {
        FILE *f = fopen("default.fnt", "rb");

        if(!f)
            printf("font default.fnt not found\n");

        font_input_stream = create_stream(f, fgetc, feof);
        font = load_font(font_input_stream);
        destroy_stream(font_input_stream);
        fclose(f);

        window = create_window();

        button = create_button(-0.91, 0, 0.9, 0.2, font, "Hello");

        button->on_click_arguments = "Hello";
        button->run_on_click = printf;

        add_element_in_window(window, button, refresh_button, destroy_button);

        button = create_button(0, 0, 0.9, 0.2, font, "World");

        button->on_click_arguments = "World";
        button->run_on_click = printf;

        add_element_in_window(window, button, refresh_button, destroy_button);

        once=0;
    }

    refresh_window(window);
}
*/

int main()
{
/*    unsigned int width             = 1440;
    unsigned int height            = 900;
    unsigned int frames_per_second = 60;

    init_graphics(width, height, frames_per_second, draw);
    start_mouse_coords_update(width, height);

    for(;;)
    {
        if(pressed_key(VK_ESCAPE))
            break;
    }
*/
    return 0;
}
