procedure initialize_curve(Curve *curve, Array *points)
{
    N_32 i;

    curve->points       = points;
    curve->coefficients = new_array(N_32, points->length);

    for(i=0; i<points->length; ++i)
    {
        curve->coefficients[i] = C(points->length, i);
    }
}


procedure deinitialize_curve(Curve *curve)
{
    free(curve->coefficients);
}


function R_32 pow(R_32 number, N_32 power)
{
    R_32 result;

    result = 1.0f;

    for(; power; --power)
        result *= number;

    return result;
}


function R_32 module(R_32 number)
{
    if(number < 0)
        number = -number;

    return number;
}


procedure draw_curve(Canvas *canvas, Curve *curve)
{
    Point *current_point;
    Point *next_point;
    R_32   t;
    N_32   i;
    N_32   j;
    R_32   x;
    R_32   y;
    R_32   step;
    Byte  *draw_point;

    step = 0;

    for(i=0; i<curve->points->length-1; ++i)
    {
        current_point = curve->points->data[i];
        next_point = curve->points->data[i+1];

        for(j=0; j<current_point->length; ++j)
            step += module(module(current_point->coords[j]) - module(next_point->coords[j]));
    }

    step = 1.0f / step;

    for(t=0.0f; t<=1.0f; t+=step)
    {
        x = 0.0f;
        y = 0.0f;

        for(i=0; i<curve->points->length; ++i)
        {
            current_point = curve->points->data[i];

            x += current_point->coords[0] * (R_32)C(curve->points->length-1, i) * pow(1.0f - t, curve->points->length-1 - i) * pow(t, i);
            y += current_point->coords[1] * (R_32)C(curve->points->length-1, i) * pow(1.0f - t, curve->points->length-1 - i) * pow(t, i);
        }

        draw_point = get_canvas_pixel(canvas, (N_32)x, (N_32)y);

        draw_point[0] = 255;
        draw_point[1] = 255;
        draw_point[2] = 255;
    }
}
