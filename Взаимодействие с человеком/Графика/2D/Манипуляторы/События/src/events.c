static Byte *pressed_border_id = 0;

/*
static function R_32 get_relative_mouse_coord_x(Program_Space *program_space)
{
    R_32 aspect;
    R_32 mouse_coord_x;

    aspect        = (R_32)program_space->width / (R_32)program_space->height;
    mouse_coord_x = 2 * get_mouse_coord_x() / (R_32)program_space->width - 1;

    return mouse_coord_x * aspect;
}


static function R_32 get_relative_mouse_coord_y(Program_Space *program_space)
{
    return 1.0 - 2 * get_mouse_coord_y() / (R_32)program_space->height;
}


static function Boolean mouse_on_border(Program_Space *program_space, function Boolean (*on_border)(Byte *border, R_32 x, R_32 y), Byte *border)
{
    R_32 aspect;
    R_32 mouse_coord_x;
    R_32 mouse_coord_y;

    aspect        = (R_32)program_space->width / (R_32)program_space->height;
    mouse_coord_x = 2 * (R_32)get_mouse_coord_x() / (R_32)program_space->width - 1;
    mouse_coord_y = 1.0 - 2 * (R_32)get_mouse_coord_y() / (R_32)program_space->height;

    return on_border(border, mouse_coord_x * aspect, mouse_coord_y);
    return on_border(border, get_mouse_coord_x(), get_mouse_coord_y());
}*/


function Boolean is_hover (function Boolean (*on_border)(Byte *border, N_32 x, N_32 y), Byte *border)
{
    if(!pressed_border_id || border == pressed_border_id)
        return on_border(border, get_mouse_coord_x(), get_mouse_coord_y());

    return 0;
}


function Boolean pressed (function Boolean (*on_border)(Byte *border, N_32 x, N_32 y), Byte *border)
{
    if(pressed_left_mouse_key() && (!border || border == pressed_border_id))
        return on_border(border, get_mouse_coord_x(), get_mouse_coord_y());

    return 0;
}


function Boolean clicked (function Boolean (*on_border)(Byte *border, N_32 x, N_32 y), Byte *border)
{
    if(!on_border(border, get_mouse_coord_x(), get_mouse_coord_y()))
    {
        if(border == pressed_border_id)
            pressed_border_id = 0;

        pressed_left_mouse_key();
        return 0;
    }

    if(pressed_left_mouse_key())
    {
        if(on_border(border, get_mouse_coord_x(), get_mouse_coord_y()))
        {
            if(!pressed_border_id)
                pressed_border_id = border;
        }
    }
    else if(border == pressed_border_id)
    {
        pressed_border_id = 0;
        return 1;
    }

    return 0;
}


function Boolean move_if_moved(
    function Boolean (*on_border)(Byte *border, N_32 x, N_32 y),
    Byte              *border,
    function N_32    (*get_border_x)(Byte *border),
    function N_32    (*get_border_y)(Byte *border),
    procedure        (*set_border_x)(Byte *border, N_32 x),
    procedure        (*set_border_y)(Byte *border, N_32 y)
)
{
    static Z_32 pressed_width;
    static Z_32 pressed_height;

    if(pressed_border_id && border != pressed_border_id)
        return 0;

    if(pressed_left_mouse_key())
    {
        if(!pressed_border_id)
        {
            if(on_border(border, get_mouse_coord_x(), get_mouse_coord_y()))
            {
                pressed_border_id = border;
                pressed_width  = get_mouse_coord_x() - get_border_x(border);
                pressed_height = get_mouse_coord_y() - get_border_y(border);
            }
        }
        else
        {
            set_border_x(border, get_mouse_coord_x() - pressed_width);
            set_border_y(border, get_mouse_coord_y() - pressed_height);
        }
    }
    else if(border == pressed_border_id)
    {
        pressed_border_id = 0;
        return 1;
    }

    return 0;
}
