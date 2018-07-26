procedure initialize_curve(Curve *curve)
{
    curve->length = 0;
    initialize_buffer(&curve->points, 5);
    initialize_buffer_output(&curve->points, &curve->points_output);
}


procedure add_point_in_curve(Curve *curve, Point *point)
{
    N_32 i;

    write_binary_N_32(&curve->points_output, point->length);

    for(i = 0; i < point->length; ++i)
        write_binary_R_32(&curve->points_output, point->coords[i]);

    ++curve->length;
}


procedure deinitialize_curve(Curve *curve)
{
    deinitialize_buffer(&curve->points);
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


private function Point* get_next_point(Point *current_point)
{
    return ((R_32*) (((N_32*)current_point) + 1)) + current_point->length;
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

    for(i = 0, current_point = curve->points.data; i < curve->length-1; ++i)
    {
        next_point = get_next_point(current_point);

        for(j=0; j<current_point->length; ++j)
            step += module(module(current_point->coords[j]) - module(next_point->coords[j]));

        current_point = get_next_point(next_point);
    }

    step = 1.0f / step;

    for(t = 0.0f; t <= 1.0f; t += step)
    {
        x = 0.0f;
        y = 0.0f;

        for(
            i = 0, current_point = curve->points.data;
            i < curve->length;
            ++i, current_point = get_next_point(current_point)
        )
        {
            x += current_point->coords[0] * (R_32)C(curve->length-1, i) * pow(1.0f - t, curve->length-1 - i) * pow(t, i);
            y += current_point->coords[1] * (R_32)C(curve->length-1, i) * pow(1.0f - t, curve->length-1 - i) * pow(t, i);
        }

        draw_point = get_canvas_pixel(canvas, (N_32)x, (N_32)y);

        draw_point[0] = 255;
        draw_point[1] = 255;
        draw_point[2] = 255;
    }
}


function Array* calculate_intersect_points_curve_with_curve(Curve *curve1, Curve *curve2)
{
    Array    *intersect_points;
    Point    *R0;
    Point    *R1;
    Point    *P0;
    Point    *P1;
    Point    *P2;
    Point_2D  new_point;
    R_32      t;
    R_32      A;
    R_32      B;
    R_32      C;
    R_32      D;
    N_32      i;

    intersect_points = new(Array);
    initialize_array(intersect_points, 1, &free_memory);

    if(curve1->length != 2)
        swap(&curve1, &curve2, sizeof(Curve*));

    if(curve1->length != 2)
        return 0;

    R0 = curve1->points.data;
    R1 = get_next_point(R1);

    if(curve2->length == 2)
    {
        P0 = curve2->points.data;
        P1 = get_next_point(P1);
        //new_point = allocate_memory(sizeof(N_32) + sizeof(R_32) * P0->length)
        //new_point->length = ;

        for(i = 0; i < P0->length; ++i)
        {
            t = P0->coords[i] - P1->coords[i] + R0->coords[i] - R1->coords[i];

            if(!t)
                break;

            t = 
        }
    }
    else if(curve2->length == 3)
    {
        P0 = curve2->points.data;
        P1 = get_next_point(P1);
        P2 = get_next_point(P2);
    }
    else
        goto error;

    return intersect_points;

error:
    deinitialize_array(intersect_points);
    free_memory(intersect_points);
}