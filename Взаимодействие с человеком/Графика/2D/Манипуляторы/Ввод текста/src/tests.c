#include <stdio.h>
#include <GL/gl.h>
#include <libs/graphics/graphics.h>
#include <libs/input/input.h>
#include "text input.h"


void draw()
{
    static Boolean     once               =  1;
    static Font       *font;
    static TextInput  *text_input;
    static TextInput  *text_input2;
    Stream            *font_input_stream;

    if(once)
    {
        FILE *f = fopen("default.fnt", "rb");

        if(!f)
            printf("font default.fnt not found\n");

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();

        font_input_stream = create_stream(f, fgetc, feof);
        font = load_font(font_input_stream);
        destroy_stream(font_input_stream);
        fclose(f);

        text_input = create_text_input(0.3, 0.3, 0.9, 0.2, font);

        text_input->active_color[0] = 0.9;
        text_input->active_color[1] = 0.9;
        text_input->active_color[2] = 0.9;


        text_input2 = create_text_input(0.3, -0.3, 0.9, 0.2, font);

        text_input2->active_color[0] = 0.9;
        text_input2->active_color[1] = 0.9;
        text_input2->active_color[2] = 0.9;

        //button->on_click_arguments = "Fd";
        //button->run_on_click = printf;

        once=0;
    }

    refresh_text_input(text_input);
    refresh_text_input(text_input2);
}


int main()
{
    unsigned int width             = 1600;
    unsigned int height            = 1200;
    unsigned int frames_per_second = 60;

    init_graphics(width, height, frames_per_second, draw);
    start_mouse_coords_update(width, height);

    for(;;)
    {
        if(pressed_key(VK_ESCAPE))
            break;
    }

    return 0;
}
