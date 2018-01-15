#include <windows.h>
#include "TGA.h"
#include <system/devices/graphics/graphics.h>
#include <system/devices/mouse/mouse.h>
#include <system/devices/keyboard/keyboard.h>
#include <human interface/graphics/2D/events/events.h>
#include <system/interfaces/files/files.h>


Canvas *image;
Canvas *contours;
N_32    texture_id = 0;

/*
procedure draw_canvas(Canvas *canvas, N_32 x, N_32 y)
{
    Byte *in;
    Byte *out;
    N_32  i;
    N_32  j;

    in = get_canvas_pixel(canvas, 0, 0);
    out = get_canvas_pixel(canvas, x, y);

    for(i=0; i<canvas->height && i<canvas->height + y; ++i)
    {
        for(j=0; j<canvas->width && j<canvas->width + x; ++j)
        {
            out[(i*canvas->width + j)*4] = in[(i*canvas->width + j)*4 + 1];
            out[(i*canvas->width + j)*4 + 1] = in[(i*canvas->width + j)*4 + 2];
            out[(i*canvas->width + j)*4 + 2] = in[(i*canvas->width + j)*4 + 3];
            //out[(i*current_canvas.width + j)*4 + 3] = in[(i*canvas->width + j)*4 + 2];
        }
    }
}*/


N_32 level = 10;




function Z_32 module(Z_32 number)
{
	if(number < 0)
		return -number;

	return number;
}


function N_32 pixel_distance(char *pixel1, char *pixel2)
{
    N_32 minimum;

    //return (pixel1[0] - pixel2[0])*(pixel1[0] - pixel2[0]) + (pixel1[1] - pixel2[1])*(pixel1[1] - pixel2[1]) + (pixel1[2] - pixel2[2])*(pixel1[2] - pixel2[2]);

    minimum = module((Z_32)pixel1[0] - (Z_32)pixel2[0]);

    if(module((Z_32)pixel1[1] - (Z_32)pixel1[1]) < minimum)
        minimum = module((Z_32)pixel1[1] - (Z_32)pixel2[1]);

    if(module((Z_32)pixel1[2] - (Z_32)pixel1[2]) < minimum)
        minimum = module((Z_32)pixel1[2] - (Z_32)pixel2[2]);
//printf("distance is %d\n", maximum);
    return minimum;
}


function Canvas* get_contours(Canvas *canvas)
{
	Canvas *new_canvas;
	N_32    x;
	N_32    y;
	Byte   *right_pixel;
	Byte   *down_pixel;
	Byte   *current_pixel;
	Byte   *new_pixel;

	new_canvas = create_canvas(canvas->width, canvas->height, canvas->bytes_per_pixel);
	clear_canvas(new_canvas);

	for(y=0; y<canvas->height-1; ++y)
	{
		for(x=0; x<canvas->width-1; ++x)
		{
			new_pixel = get_canvas_pixel(new_canvas, x, y);
			current_pixel = get_canvas_pixel(canvas, x, y);
			right_pixel = get_canvas_pixel(canvas, x+1, y);
			down_pixel = get_canvas_pixel(canvas, x, y+1);

			Z_32 d = level;

			if(
                pixel_distance(current_pixel, down_pixel) > d
                || pixel_distance(current_pixel, right_pixel) > d
				/*module((Z_32)current_pixel[0] - (Z_32)down_pixel[0]) > d
                || module((Z_32)current_pixel[1] - (Z_32)down_pixel[1]) > d
                || module((Z_32)current_pixel[2] - (Z_32)down_pixel[2]) > d*/
			)
			    {
                    new_pixel[0] = 255;
                    new_pixel[1] = 255;
                    new_pixel[2] = 255;
			    }
		}
	}

	return new_canvas;
}


typedef struct
{
    N_32 x;
    N_32 y;
}
Point_2D;


function Boolean distances_contains(Point_2D *distances, N_32 length, N_32 x, N_32 y)
{
    N_32 i;

    for(i=0; i<length; ++i)
        if(distances[i].x == x && distances[i].y == y)
            return 1;

    return 0;
}


procedure normal_contour(Canvas *image, Canvas *contours, N_32 x, N_32 y)
{
    N_32     i;
    Point_2D distances[200];
    N_32     length_distances;
    Byte    *current_pixel;
    Byte    *minimum_pixel;
    N_32     minimum_distance;
    Byte    *left_pixel;
    Byte    *right_pixel;
    Byte    *top_pixel;
    Byte    *bottom_pixel;

    Byte    *top_left_pixel;
    Byte    *top_right_pixel;
    Byte    *bottom_left_pixel;
    Byte    *bottom_right_pixel;

    Byte    *new_pixel;

    length_distances = 0;

    for(i=0; i<10; ++i)
    {
        current_pixel = get_canvas_pixel(image, x, y);
        left_pixel    = get_canvas_pixel(image, x-1, y);
        right_pixel   = get_canvas_pixel(image, x+1, y);
        top_pixel     = get_canvas_pixel(image, x, y-1);
        bottom_pixel  = get_canvas_pixel(image, x, y+1);

        top_left_pixel     = get_canvas_pixel(image, x-1, y+1);
        top_right_pixel    = get_canvas_pixel(image, x+1, y+1);
        bottom_left_pixel  = get_canvas_pixel(image, x-1, y-1);
        bottom_right_pixel = get_canvas_pixel(image, x+1, y-1);

        new_pixel = get_canvas_pixel(image, x, y);//get_canvas_pixel(contours, x, y);

        new_pixel[0] = 255;
        new_pixel[1] = 0;
        new_pixel[2] = 0;

        distances[length_distances].x = x;
        distances[length_distances].y = y;
        ++length_distances;

        if(!distances_contains(distances, length_distances, x-1, y))
            minimum_pixel = left_pixel;
        else if(!distances_contains(distances, length_distances, x+1, y))
            minimum_pixel = right_pixel;
        else if(!distances_contains(distances, length_distances, x, y-1))
            minimum_pixel = bottom_pixel;
        else if(!distances_contains(distances, length_distances, x, y+1))
            minimum_pixel = top_pixel;

        else if(!distances_contains(distances, length_distances, x-1, y+1))
            minimum_pixel = top_left_pixel;
        else if(!distances_contains(distances, length_distances, x+1, y+1))
            minimum_pixel = top_right_pixel;
        else if(!distances_contains(distances, length_distances, x-1, y-1))
            minimum_pixel = bottom_left_pixel;
        else if(!distances_contains(distances, length_distances, x+1, y-1))
            minimum_pixel = bottom_right_pixel;

        else
            return;

        minimum_distance = pixel_distance(minimum_pixel, current_pixel);

        if(!distances_contains(distances, length_distances, x-1, y) && pixel_distance(left_pixel, current_pixel) < minimum_distance)
        {
            minimum_pixel = left_pixel;
            minimum_distance = pixel_distance(left_pixel, current_pixel);
        }

        if(!distances_contains(distances, length_distances, x+1, y) && pixel_distance(right_pixel, current_pixel) < minimum_distance)
        {
            minimum_pixel = right_pixel;
            minimum_distance = pixel_distance(right_pixel, current_pixel);
        }

        if(!distances_contains(distances, length_distances, x, y+1) && pixel_distance(top_pixel, current_pixel) < minimum_distance)
        {
            minimum_pixel = top_pixel;
            minimum_distance = pixel_distance(top_pixel, current_pixel);
        }

        if(!distances_contains(distances, length_distances, x, y-1) && pixel_distance(bottom_pixel, current_pixel) < minimum_distance)
        {
            minimum_pixel = bottom_pixel;
            minimum_distance = pixel_distance(bottom_pixel, current_pixel);
        }


        if(!distances_contains(distances, length_distances, x-1, y+1) && pixel_distance(top_left_pixel, current_pixel) < minimum_distance)
        {
            minimum_pixel = top_left_pixel;
            minimum_distance = pixel_distance(top_left_pixel, current_pixel);
        }

        if(!distances_contains(distances, length_distances, x+1, y+1) && pixel_distance(top_right_pixel, current_pixel) < minimum_distance)
        {
            minimum_pixel = top_right_pixel;
            minimum_distance = pixel_distance(top_right_pixel, current_pixel);
        }

        if(!distances_contains(distances, length_distances, x-1, y-1) && pixel_distance(bottom_left_pixel, current_pixel) < minimum_distance)
        {
            minimum_pixel = bottom_left_pixel;
            minimum_distance = pixel_distance(bottom_left_pixel, current_pixel);
        }

        if(!distances_contains(distances, length_distances, x+1, y-1) && pixel_distance(bottom_right_pixel, current_pixel) < minimum_distance)
        {
            minimum_pixel = bottom_right_pixel;
            minimum_distance = pixel_distance(bottom_right_pixel, current_pixel);
        }


        if(minimum_pixel == left_pixel)
        {
            //printf("left\n");
            --x;
        }

        if(minimum_pixel == right_pixel)
        {
            //printf("right\n");
            ++x;
        }

        if(minimum_pixel == top_pixel)
        {
            //printf("top\n");
            ++y;
        }

        if(minimum_pixel == bottom_pixel)
        {
            //printf("bottom\n");
            --y;
        }


        if(minimum_pixel == top_left_pixel)
        {
            //printf("top left\n");
            --x;
            ++y;
        }

        if(minimum_pixel == top_right_pixel)
        {
            //printf("top right\n");
            ++x;
            ++y;
        }

        if(minimum_pixel == bottom_left_pixel)
        {
            //printf("bottom left\n");
            --x;
            --y;
        }

        if(minimum_pixel == bottom_right_pixel)
        {
            //printf("bottom right\n");
            ++x;
            --y;
        }
    }
}


function Canvas* get_contour(Canvas *contours)
{
    Canvas *new_canvas;
    N_32    x;
	N_32    y;
	Byte   *new_pixel;
	Byte   *current_pixel;
	Byte   *right_pixel;
	Byte    is_inline;

    new_canvas = create_canvas(contours->width, contours->height, contours->bytes_per_pixel);
	clear_canvas(new_canvas);
//return new_canvas;
	is_inline = 0;

	for(y=0; y<contours->height-1; ++y)
	{
		for(x=0; x<contours->width-1; ++x)
		{
			new_pixel = get_canvas_pixel(new_canvas, x, y);
			current_pixel = get_canvas_pixel(contours, x, y);
			right_pixel = get_canvas_pixel(contours, x+1, y);
			//down_pixel = get_canvas_pixel(contours, x, y+1);

			if(is_inline)
            {
                if(*current_pixel)
                {

                }
                else
                {
                    is_inline = !is_inline;

                    new_pixel[0] = 255;
                    new_pixel[1] = 255;
                    new_pixel[2] = 255;
                }
            }
            else
            {
                if(!*current_pixel)
                {

                }
                else
                {
                    is_inline = !is_inline;
/*
                    new_pixel[0] = 255;
                    new_pixel[1] = 255;
                    new_pixel[2] = 255;*/
                }
            }
		}
	}

	return new_canvas;
}


function Canvas* get_final(Canvas *contours)
{
    Canvas *new_canvas;
    N_32    x;
	N_32    y;
	Byte   *new_pixel;
	Byte   *current_pixel;
	Byte   *right_pixel;
	Byte    is_inline;

    new_canvas = create_canvas(contours->width, contours->height, contours->bytes_per_pixel);
	clear_canvas(new_canvas);

	for(y=10; y<contours->height-10; ++y)
	{
		for(x=10; x<contours->width-10; ++x)
		{
			new_pixel = get_canvas_pixel(new_canvas, x, y);
			current_pixel = get_canvas_pixel(contours, x, y);
			right_pixel = get_canvas_pixel(contours, x+1, y);

			if(*current_pixel)
                normal_contour(image, new_canvas, x, y);
		}
	}

	return new_canvas;
}


void draw(Canvas *main_canvas)
{
    static Rectangle  rectangle;
    static Boolean    once = 0;
    static Canvas    *contours;
    static Canvas    *contour;
    static Canvas    *final;

    if(!once)
    {
        rectangle.x = 0;
        rectangle.y = 0;
        rectangle.width = image->width;
        rectangle.height = image->height;

        contours = get_contours(image);
        contour = get_contour(contours);
        final = get_final(contour);

        once = 1;
    }

    //clear_canvas(main_canvas);
    //draw_canvas(canvas, rectangle.x, rectangle.y);
    //draw_canvas(canvas, get_mouse_coord_x(), get_mouse_coord_y());
    //draw_canvas(canvas, get_mouse_coord_x() - 512, get_mouse_coord_y());

    //move_if_moved(&on_rectangle, &rectangle, &get_rectangle_x, &get_rectangle_y, &set_rectangle_x, &set_rectangle_y);

    draw_canvas_on_canvas(main_canvas, image, 0, 0);
    //draw_canvas_on_canvas(main_canvas, contours, image->width, 0);
    draw_canvas_on_canvas(main_canvas, contour, image->width, 0);
    //draw_canvas_on_canvas(main_canvas, contour, image->width, 0);
/*
	if(pressed_key('W') && level < 255)
    {
        ++level;
        destroy_canvas(contours);
        contours = get_contours(image);
        destroy_canvas(contour);
        contour = get_contour(contours);
    }

    if(pressed_key('S') && level > 0)
    {
        --level;
        destroy_canvas(contours);
        contours = get_contours(image);
        destroy_canvas(contour);
        contour = get_contour(contours);
    }*/
}


function int main()
{
	Input input;

	initialize_file_input(&input, "a.tga");
	image = load_TGA(&input);
	deinitialize_input(&input);
	//contours = get_contours(canvas);

    initialize_graphics(1440, 900, 100, draw);

    for(;;);

    return 0;
}
