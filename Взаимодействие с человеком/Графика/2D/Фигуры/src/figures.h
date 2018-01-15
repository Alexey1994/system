#ifndef GRAPHICS_2D_FIGURES_H_INCLUDED
#define GRAPHICS_2D_FIGURES_H_INCLUDED


#include <extends/extends.h>
#include <human interface/graphics/canvas/canvas.h>


typedef struct
{
    N_32 x;
    N_32 y;
    N_32 width;
    N_32 height;
}
Rectangle;


function  Rectangle* create_rectangle     (N_32 x, N_32 y, N_32 width, N_32 height);
procedure            destroy_rectangle    (Rectangle *rectangle);

procedure            initialize_rectangle (Rectangle *rectangle, N_32 x, N_32 y, N_32 width, N_32 height);

function  Boolean    on_rectangle         (Rectangle *rectangle, N_32 x, N_32 y);
function  N_32       get_rectangle_x      (Rectangle *rectangle);
function  N_32       get_rectangle_y      (Rectangle *rectangle);
procedure            set_rectangle_x      (Rectangle *rectangle, N_32 x);
procedure            set_rectangle_y      (Rectangle *rectangle, N_32 y);

procedure            draw_rectangle       (Canvas *canvas, Rectangle *rectangle);


#include "figures.c"

#endif // GRAPHICS_2D_FIGURES_H_INCLUDED
