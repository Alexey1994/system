void build_vector_by_points (Vector *vector, Point *p1, Point *p2)
{
    int i;

    initialize_point(vector, p1->length);

    for(i=0; i<p1->length; ++i)
        vector->coords[i] = p2->coords[i] - p1->coords[i];
}


float vector_length (Vector *vector)
{
    int   i;
    float result;

    result = 0;

    for(i=0; i<vector->length; ++i)
        result += vector->coords[i] * vector->coords[i];

    return sqrt(result);
}


float dot_product(Vector *a, Vector *b)
{
    int   i;

    float result = 0;

    for(i=0; i<a->length; ++i)
        result += a->coords[i] * b->coords[i];

    return result;
}


Vector* cross_product(Vector *a, Vector *b)
{
    return create_3D_point(
        a->coords[1]*b->coords[2] - a->coords[2]*b->coords[1],
        a->coords[2]*b->coords[0] - a->coords[0]*b->coords[2],
        a->coords[0]*b->coords[1] - a->coords[1]*b->coords[0]
    );
}


void normalize_vector(Vector *vector)
{
    int   i;
    float length = 0;

    for(i=0; i<vector->length; ++i)
        length += vector->coords[i]*vector->coords[i];

    length = sqrt(length);

    for(i=0; i<vector->length; ++i)
        vector->coords[i] /= length;
}
