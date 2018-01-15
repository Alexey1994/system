#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED


#include <system/interfaces/thread/thread.h>
#include <human interface/graphics/canvas/canvas.h>


procedure initialize_graphics (N_32 width, N_32 height, N_32 frames_per_second, procedure (*draw)(Canvas *canvas));


#include "graphics.c"

#endif // GRAPHICS_H_INCLUDED
