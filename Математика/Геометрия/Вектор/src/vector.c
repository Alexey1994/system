procedure build_vector_by_points (Vector *vector, Point *p1, Point *p2)
{
    N_32 i;

    vector->length = p1->length;

    for(i=0; i<p1->length; ++i)
        vector->coords[i] = p2->coords[i] - p1->coords[i];
}


function R_32 vector_length (Vector *vector)
{
    N_32 i;
    R_32 result;

    result = 0;

    for(i=0; i<vector->length; ++i)
    {
        R_32 coord = vector->coords[i];
        result += coord * coord;
    }

    return sqrt(result);
}


function R_32 dot_product (Vector *a, Vector *b)
{
    N_32 i;
    R_32 result;

    result = 0;

    for(i=0; i<a->length; ++i)
        result += a->coords[i] * b->coords[i];

    return result;
}


function Vector* cross_product (Vector *a, Vector *b)
{
    /*return create_3D_point(
        a->coords[1]*b->coords[2] - a->coords[2]*b->coords[1],
        a->coords[2]*b->coords[0] - a->coords[0]*b->coords[2],
        a->coords[0]*b->coords[1] - a->coords[1]*b->coords[0]
    );*/
}


procedure normalize_vector (Vector *vector)
{
    R_32 length;
    N_32 i;

    length = vector_length(vector);

    if(!length)
        return;

    length = 1.0 / length;

    for(i=0; i<vector->length; ++i)
        vector->coords[i] *= length;
}
