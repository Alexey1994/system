#ifndef CANVAS_H_INCLUDED
#define CANVAS_H_INCLUDED


#include <extends/extends.h>


typedef struct
{
	N_32  width;
	N_32  height;
	N_8   bytes_per_pixel;

	Byte *data;
	N_32  current_color;
}
Canvas;


procedure         initialize_canvas           (Canvas *canvas, N_32 width, N_32 height, N_8 bytes_per_pixel);
procedure         deinitialize_canvas         (Canvas *canvas);
function  Canvas* create_canvas               (N_32 width, N_32 height, N_8 bytes_per_pixel);
procedure         destroy_canvas              (Canvas *canvas);

procedure         clear_canvas                (Canvas *canvas);
function  Byte*   get_canvas_pixel            (Canvas *canvas, N_32 x, N_32 y);
function  Byte*   get_percentage_canvas_pixel (Canvas *canvas, R_32 x_percents, R_32 y_percents);
procedure         set_canvas_color            (Canvas *canvas, Byte r, Byte g, Byte b, Byte alpha);
procedure         fill_canvas_pixel           (Canvas *canvas, N_32 *pixel);
procedure         draw_canvas_on_canvas       (Canvas *out, Canvas *in, N_32 x, N_32 y);


#include "canvas.c"

#endif //CANVAS_H_INCLUDED
