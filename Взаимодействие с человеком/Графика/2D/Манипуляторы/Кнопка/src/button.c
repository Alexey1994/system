procedure initialize_button(Button *button, Canvas *program_space, N_32 x, N_32 y, N_32 width, N_32 height, Raster_Font *font, Character *text)
{
    button->program_space                 = program_space;

    button->border.x                      =  x;
    button->border.y                      =  y;
    button->border.width                  =  width;
    button->border.height                 =  height;

    button->font                          =  font;
    button->text                          =  text;

    button->background_unactive_color[0]  =  128;
    button->background_unactive_color[1]  =  128;
    button->background_unactive_color[2]  =  128;

    button->background_active_color[0]    =  64;
    button->background_active_color[1]    =  64;
    button->background_active_color[2]    =  64;

    button->background_pressed_color[0]   =  0;
    button->background_pressed_color[1]   =  0;
    button->background_pressed_color[2]   =  0;

    button->on_click_arguments            =  0;
    button->run_on_click                  =  0;
}


static void draw_button_text(Button *button)
{
    N_32 text_x;
    N_32 text_y;

    text_x = button->border.x + (button->border.width - text_width(button->text, button->font)) / 2;
    text_y = button->border.y + (button->border.height - text_height(button->text, button->font)) / 2;

    print(button->program_space, button->text, text_x, text_y, button->font);
}


static void draw_button_background(Button *button)
{
    if(pressed(&on_rectangle, &button->border))
        set_canvas_color(button->program_space, button->background_pressed_color[0], button->background_pressed_color[1], button->background_pressed_color[2], 255);
    else if(is_hover(&on_rectangle, &button->border))
        set_canvas_color(button->program_space, button->background_active_color[0], button->background_active_color[1], button->background_active_color[2], 255);
    else
        set_canvas_color(button->program_space, button->background_unactive_color[0], button->background_unactive_color[1], button->background_unactive_color[2], 255);

    draw_rectangle(button->program_space, &button->border);
}


static void draw_button(Button *button)
{
    draw_button_background(button);
    draw_button_text(button);
}


static void update_button_state(Button *button)
{
    if(clicked(&on_rectangle, &button->border))
        button->run_on_click(button->on_click_arguments);
}


void refresh_button(Button *button)
{
    update_button_state(button);
    draw_button(button);
}
