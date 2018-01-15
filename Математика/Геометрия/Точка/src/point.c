procedure initialize_point (Point *point, N_32 length)
{
    point->length = length;
}


procedure initialize_point_2D (Point_2D *point, R_32 x, R_32 y)
{
    point->length = 2;
    point->x = x;
    point->y = y;
}


procedure initialize_point_3D (Point_3D *point, R_32 x, R_32 y, R_32 z)
{
    point->length = 3;
    point->x = x;
    point->y = y;
    point->z = z;
}


procedure initialize_point_from_point (Point *p1, Point *p2)
{
    p1->length = p2->length;
}


procedure copy_point (Point *result, Point *source)
{
    N_32 i;

    result->length = source->length;

    for(i=0; i<source->length; ++i)
        result->coords[i] = source->coords[i];
}


procedure draw_point (Point *point, Canvas *canvas)
{
    Byte *pixel;

    if(point->length == 2)
    {
        pixel = get_canvas_pixel(canvas, point->coords[0], point->coords[1]);
        pixel[0] = 255;
    }
}