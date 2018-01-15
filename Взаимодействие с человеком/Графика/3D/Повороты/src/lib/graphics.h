#ifndef GRAPHICS_H_INCLUDED
#define GRAPHICS_H_INCLUDED


extern float aspect;
extern float width_pixel;
extern float height_pixel;


void init_graphics(unsigned int width, unsigned int height, unsigned int frames_per_second, void(*draw)());


#endif // GRAPHICS_H_INCLUDED
