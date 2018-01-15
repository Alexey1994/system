procedure initialize_line (Line *line, Point *begin, Point *end)
{
	line->begin = begin;
	line->end   = end;
}

/*
function Line* create_line (Point *begin, Point *end)
{
	Line *line;

	line = new(Line);
	initialize_line(line, begin, end);
	return line;
}


procedure destroy_line (Line *line)
{
	free(line);
}*/


procedure draw_line (Line *line, Canvas *canvas)
{
	//Vector *line_vector;
	R_32    line_length;
	R_32    t;
	R_32    step;
	N_32    i;
	Point  *result;
	Vector *line_vector;

	//line_vector = alloca(sizeof(Vector) + sizeof(R_32) * line->begin->length);
	//result = alloca(sizeof(Point) + sizeof(R_32) * line->begin->length);

	initialize_point(line_vector, line->begin->length);
	initialize_point(result, line->begin->length);

	printf("%d\n", line_vector->length);

	build_vector_by_points(&line_vector, line->begin, line->end);
	line_length = vector_length(&line_vector);

	for(t = 0; t <= line_length; ++t)
	{
		for(i=0; i<result->length; ++i)
			result->coords[i] = line->begin->coords[i] + t * line_vector->coords[i] / line_length;

		draw_point(result, canvas);
	}
/*
	line_vector = create_point(line->begin->length);
	build_vector_by_points(line_vector, line->begin, line->end);
	line_length = vector_length(line_vector);
	step = 1.0f / line_length;
	result = create_point(line->begin->length);

	for(t = 0; t <= 1.0f; t += step)
	{
		for(i=0; i<result->length; ++i)
			result->coords[i] = line->begin->coords[i] + t * line_vector->coords[i];

		draw_point(result, canvas);
	}

	destroy_point(line_vector);
	destroy_point(result);
*/
}
