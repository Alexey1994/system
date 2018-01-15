#include <libs/graphics/geometry/vector/vector.h>


procedure initialize_line (Line *line, Point *begin, Point *end)
{
	copy_point(&line->begin, begin);
	copy_point(&line->end, end);
}


procedure deinitialize_line (Line *line)
{
	deinitialize_point(&line->begin);
	deinitialize_point(&line->end);
}


function Line* create_line (Point *begin, Point *end)
{
	Line *line;

	line = new(Line);
	initialize_line(line, begin, end);
	return line;
}


procedure destroy_line (Line *line)
{
	deinitialize_line(line);
	free(line);
}


procedure rasterize_line (Line *line, Canvas *canvas)
{
	Vector line_vector;
	R_32   line_length;
	R_32   t;
	R_32   step;
	N_32   i;
	Point  result;

	build_vector_by_points(&line_vector, &line->begin, &line->end);
	line_length = vector_length(&line_vector);
	step = 1.0f / line_length / (float)canvas->width;
	initialize_point(&result, line->begin.length);

	for(t = 0; t <= 1.0f; t += step)
	{
		for(i=0; i<result.length; ++i)
			result.coords[i] = line->begin.coords[i] + t * line_vector.coords[i];

		rasterize_point(&result, canvas);
	}

	deinitialize_point(&line_vector);
	deinitialize_point(&result);
}