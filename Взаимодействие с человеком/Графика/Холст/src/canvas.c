procedure initialize_canvas (Canvas *canvas, N_32 width, N_32 height, N_8 bytes_per_pixel)
{
	canvas->width           = width;
	canvas->height          = height;
	canvas->bytes_per_pixel = bytes_per_pixel;
	canvas->data            = new_array(Byte, width * height * bytes_per_pixel);
}


procedure deinitialize_canvas (Canvas *canvas)
{
	free_memory(canvas->data);
}


function Canvas* create_canvas (N_32 width, N_32 height, N_8 bytes_per_pixel)
{
	Canvas *canvas = new(Canvas);
	initialize_canvas(canvas, width, height, bytes_per_pixel);
	return canvas;
}


procedure destroy_canvas (Canvas *canvas)
{
	deinitialize_canvas(canvas);
	free_memory(canvas);
}


procedure clear_canvas (Canvas *canvas)
{
	Z_32  i;
	N_32  canvas_memory_size;
	N_32 *data;

	canvas_memory_size = canvas->width * canvas->height * canvas->bytes_per_pixel / 4;
	data = canvas->data;

	for(i=0; i<canvas_memory_size; ++i)
		data[i] = 0;
}


function Byte* get_canvas_pixel (Canvas *canvas, N_32 x, N_32 y)
{
	return canvas->data + (canvas->width * y + x) * canvas->bytes_per_pixel;
}

/*
function Byte* get_percentage_canvas_pixel (Canvas *canvas, R_32 x_percents, R_32 y_percents)
{
	N_32 x;
	N_32 y;

	if(x_percents > 1.0f)
		x_percents = 1.0f;

	if(x_percents < 0)
		x_percents = 0;

	if(y_percents > 1.0f)
		y_percents = 1.0f;

	if(y_percents < 0)
		y_percents = 0;

	x = x_percents * (R_32)canvas->width;
	y = y_percents * (R_32)canvas->height;

	return get_canvas_pixel(canvas, x, y);
}*/


procedure set_canvas_color (Canvas *canvas, Byte r, Byte g, Byte b, Byte alpha)
{
    canvas->current_color = alpha + (r<<8) + (g<<16) + (b<<24);
	/*canvas->current_color[0] = alpha;
	canvas->current_color[1] = r;
	canvas->current_color[2] = g;
	canvas->current_color[3] = b;*/
}


procedure fill_canvas_pixel (Canvas *canvas, N_32 *pixel)
{
    *pixel = canvas->current_color;
}


procedure draw_canvas_on_canvas (Canvas *out, Canvas *in, N_32 x, N_32 y)
{
	Byte *out_pixel;
	Byte *in_pixel;
	N_32  i;
	N_32  j;

	for(i=0; i<in->height; ++i)
	{
		if(i + y >= out->height)
			break;

		for(j=0; j<in->width; ++j)
		{
			in_pixel = get_canvas_pixel(in, j, i);

			if(j + x >= out->width)
				break;

			out_pixel = get_canvas_pixel(out, j + x, i + y);

			out_pixel[0] = in_pixel[0];
			out_pixel[1] = in_pixel[1];
			out_pixel[2] = in_pixel[2];
			out_pixel[3] = in_pixel[3];
/*
			//out_pixel[3] = out_pixel[3] * (255 - in_pixel[3]) / 255;
			out_pixel[0] = out_pixel[0] * (255 - in_pixel[3]) / 255 + in_pixel[0] * in_pixel[3] / 255;
			out_pixel[1] = out_pixel[1] * (255 - in_pixel[3]) / 255 + in_pixel[1] * in_pixel[3] / 255;
			out_pixel[2] = out_pixel[2] * (255 - in_pixel[3]) / 255 + in_pixel[2] * in_pixel[3] / 255;
*/
		}
	}
}
