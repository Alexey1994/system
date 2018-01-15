void initialize_point(Point *point, int length)
{
    point->length = length;
    point->coords = new_array(float, length);
}


void initialize_3D_point(Point *point, float x, float y, float z)
{
    initialize_point(point, 3);

    point->coords[0] = x;
    point->coords[1] = y;
    point->coords[2] = z;
}


void initialize_point_from_point(Point *p1, Point *p2)
{
    int i;

    deinitialize_point(p1);
    initialize_point(p1, p2->length);

    for(i=0; i<p2->length; ++i)
        p1->coords[i] = p2->coords[i];
}


void deinitialize_point(Point *point)
{
    free(point->coords);
}


Point* create_point(int length)
{
    Point *point = new(Point);

    initialize_point(point, length);

    return point;
}


Point* create_3D_point(float x, float y, float z)
{
    Point *point = create_point(3);

    initialize_3D_point(point, x, y, z);

    return point;
}


void destroy_point(Point *point)
{
    deinitialize_point(point);
    free(point);
}


void copy_point (Point *result, Point *source)
{
    int i;

    initialize_point(result, source->length);

    for(i=0; i<source->length; ++i)
        result->coords[i] = source->coords[i];
}


void rasterize_point (Point *point, Canvas *canvas)
{
    Byte *pixel;

    if(point->length == 2)
    {
        pixel = get_percentage_canvas_pixel(canvas, point->coords[0], point->coords[1]);
        pixel[0] = 255;
    }
}