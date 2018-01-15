#ifndef MOUSE_H_INCLUDED
#define MOUSE_H_INCLUDED


//#include <extends/extends.h>
//#include <system/interfaces/thread/thread.h>
//#include <system/devices/graphics/graphics.h>


//extern R_32 mouse_coord_x;
//extern R_32 mouse_coord_y;


function  Boolean pressed_left_mouse_key    ();
function  Boolean pressed_right_mouse_key   ();
function  N_32    get_mouse_coord_x         ();
function  N_32    get_mouse_coord_y         ();
//procedure         start_mouse_coords_update (N_32 display_width, N_32 display_height);


#include "mouse.c"

#endif //MOUSE_H_INCLUDED
