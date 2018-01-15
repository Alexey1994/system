#ifndef EVENTS_H_INCLUDED
#define EVENTS_H_INCLUDED


#include <extends/extends.h>
#include <human interface/graphics/2D/figures/figures.h>
#include <system/devices/mouse/mouse.h>


function Boolean is_hover (function Boolean (*on_border)(Byte *border, N_32 x, N_32 y), Byte *border);
function Boolean pressed  (function Boolean (*on_border)(Byte *border, N_32 x, N_32 y), Byte *border);
function Boolean clicked  (function Boolean (*on_border)(Byte *border, N_32 x, N_32 y), Byte *border);

function Boolean move_if_moved(
	function Boolean (*on_border)(Byte *border, N_32 x, N_32 y),
	Byte              *border,
	function N_32    (*get_border_x)(Byte *border),
	function N_32    (*get_border_y)(Byte *border),
	procedure        (*set_border_x)(Byte *border, N_32 x),
	procedure        (*set_border_y)(Byte *border, N_32 y)
);


#include "events.c"

#endif // EVENTS_H_INCLUDED
