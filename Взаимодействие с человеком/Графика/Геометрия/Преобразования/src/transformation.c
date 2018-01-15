#include <libs/extends/extends.h>


void initialize_rotate(Rotate *rotate, float angle, Vector *vector)
{
    rotate->angle  = angle;
    rotate->vector = vector;
    rotate->matrix = create_3x3_matrix(
        cos(angle)+(1-cos(angle))*vector->coords[0]*vector->coords[0],
        (1-cos(angle))*vector->coords[0]*vector->coords[1] - sin(angle)*vector->coords[2],
        (1-cos(angle))*vector->coords[0]*vector->coords[2] + sin(angle)*vector->coords[1],

        (1-cos(angle))*vector->coords[1]*vector->coords[0] + sin(angle)*vector->coords[2],
        cos(angle) + (1-cos(angle))*vector->coords[1]*vector->coords[1],
        (1-cos(angle))*vector->coords[1]*vector->coords[2] - sin(angle)*vector->coords[0],

        (1-cos(angle))*vector->coords[2]*vector->coords[0] - sin(angle)*vector->coords[1],
        (1-cos(angle))*vector->coords[2]*vector->coords[1] + sin(angle)*vector->coords[0],
        cos(angle)+(1-cos(angle))*vector->coords[2]*vector->coords[2]
    );
}


void deinitialize_rotate(Rotate *rotate)
{
    destroy_matrix(rotate->matrix);
}


Rotate* create_rotate(float angle, Vector *vector)
{
    Rotate *rotate = new(Rotate);

    initialize_rotate(rotate, angle, vector);

    return rotate;
}


void destroy_rotate(Rotate *rotate)
{
    deinitialize_rotate(rotate);
    free(rotate);
}


Point* rotate_point(Point *point, Rotate *rotate)
{
    Vector *rotated_vector = multiply_matrix_by_vector(rotate->matrix, point);

    //initialize_point_from_point(point, rotated_vector);
    //destroy_point(rotated_vector);

    return rotated_vector;
}


void initialize_scale(Scale *scale, Vector *vector)
{
    scale->vector = vector;
    /*
    scale->matrix = create_3D_matrix(
        vector->coords[0], 0, 0,
        0, vector->coords[1], 0,
        0, 0, vector->coords[2]
    );*/
}


void deinitialize_scale(Scale *scale)
{

}


Scale* create_scale(Vector *vector)
{
    Scale *scale = new(Scale);

    initialize_scale(scale, vector);

    return scale;
}


void destroy_scale(Scale *scale)
{
    deinitialize_scale(scale);
    free(scale);
}


Point* scale_point(Point *point, Scale *scale)
{
    int    i;
    Point *new_point = create_point(point->length);
    initialize_point_from_point(new_point, point);

    for(i=0; i<new_point->length; ++i)
        new_point->coords[i] *= scale->vector->coords[i];

    return new_point;
    //return multiply_matrix_by_vector(scale->matrix, point);
}


void initialize_translate(Translate *translate, Vector *vector)
{
    translate->vector = vector;
}


void reinitialize_translate(Translate *translate, Vector *vector)
{

}


void deinitialize_translate(Translate *translate)
{

}


Translate* create_translate(Vector *vector)
{
    Translate *translate = new(Translate);

    initialize_translate(translate, vector);

    return translate;
}


void destroy_translate(Translate *translate)
{
    deinitialize_translate(translate);
    free(translate);
}


Point* translate_point(Point *point, Translate *translate)
{
    int    i;
    Point *new_point = create_point(point->length);
    initialize_point_from_point(new_point, point);

    for(i=0; i<new_point->length; ++i)
        new_point->coords[i] += translate->vector->coords[i];

    return new_point;
}
