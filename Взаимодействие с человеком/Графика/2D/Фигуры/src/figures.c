function Rectangle* create_rectangle (N_32 x, N_32 y, N_32 width, N_32 height)
{
    Rectangle *rectangle = new(Rectangle);
    initialize_rectangle(rectangle, x, y, width, height);
    return rectangle;
}


procedure destroy_rectangle (Rectangle *rectangle)
{
    free(rectangle);
}


procedure initialize_rectangle (Rectangle *rectangle, N_32 x, N_32 y, N_32 width, N_32 height)
{
    rectangle->x      = x;
    rectangle->y      = y;
    rectangle->width  = width;
    rectangle->height = height;
}


function Boolean on_rectangle (Rectangle *rectangle, N_32 x, N_32 y)
{
    if(
        x >= rectangle->x && x <= rectangle->x + rectangle->width &&
        y >= rectangle->y && y <= rectangle->y + rectangle->height)
            return 1;

    return 0;
}


function N_32 get_rectangle_x (Rectangle *rectangle)
{
    return rectangle->x;
}


function N_32 get_rectangle_y (Rectangle *rectangle)
{
    return rectangle->y;
}


procedure set_rectangle_x (Rectangle *rectangle, N_32 x)
{
    rectangle->x = x;
}


procedure set_rectangle_y (Rectangle *rectangle, N_32 y)
{
    rectangle->y = y;
}


procedure draw_rectangle (Canvas *canvas, Rectangle *rectangle)
{
    N_32  x;
    N_32  y;
    Byte *line;
    N_32  rectangle_width;
    N_32  rectangle_height;

    if(rectangle->x >= canvas->width || rectangle->y >= canvas->height)
        return;

    if(rectangle->x + rectangle->width < canvas->width)
        rectangle_width = rectangle->width;
    else
        rectangle_width = canvas->width - rectangle->x;

    if(rectangle->y + rectangle->height < canvas->height)
        rectangle_height = rectangle->height;
    else
        rectangle_height = canvas->height - rectangle->y;

    for(y=0; y<rectangle_height; ++y)
    {
        line = get_canvas_pixel(canvas, rectangle->x, y + rectangle->y);

        for(x=0; x<rectangle_width; ++x)
        {
            line[x*canvas->bytes_per_pixel] = canvas->current_color[0];
            line[x*canvas->bytes_per_pixel + 1] = canvas->current_color[1];
            line[x*canvas->bytes_per_pixel + 2] = canvas->current_color[2];
            line[x*canvas->bytes_per_pixel + 3] = canvas->current_color[3];
            //line[x*canvas->bytes_per_pixel + 1] = 255;
        }
    }
}
