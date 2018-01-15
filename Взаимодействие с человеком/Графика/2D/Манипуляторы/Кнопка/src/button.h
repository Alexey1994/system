#ifndef BUTTON_H_INCLUDED
#define BUTTON_H_INCLUDED


#include <human interface/graphics/2D/fonts/raster font/raster font.h>
#include <human interface/graphics/2D/figures/figures.h>
#include <human interface/graphics/2D/events/events.h>


typedef struct
{
    Canvas        *program_space;
    Rectangle      border;
    Raster_Font   *font;
    Character     *text;

    Byte           background_unactive_color[3];
    Byte           background_active_color[3];
    Byte           background_pressed_color[3];

    Byte          *on_click_arguments;
    void         (*run_on_click)(Byte *arguments);
}
Button;


procedure initialize_button(Button *button, Canvas *program_space, N_32 x, N_32 y, N_32 width, N_32 height, Raster_Font *font, Character *text);
void refresh_button(Button *button);
//void add_button(Button *button);


#include "button.c"

#endif // BUTTON_H_INCLUDED
