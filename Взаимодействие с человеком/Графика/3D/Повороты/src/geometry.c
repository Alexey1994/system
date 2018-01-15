#include "geometry.h"
#include "arithmetic.h"


void build_vector_by_points(Point *start, Point *end, Vector *result)
{
    result->x = end->x - start->x;
    result->y = end->y - start->y;
    result->z = end->z - start->z;
}


void cross_product(Vector *a, Vector *b, Vector *result_normal)
{
    result_normal->x = a->y*b->z - a->z*b->y;
    result_normal->y = a->z*b->x - a->x*b->z;
    result_normal->z = a->x*b->y - a->y*b->x;
}


float dot_product(Vector *a, Vector *b)
{
    return a->x*b->x + a->y*b->y + a->z*b->z;
}


void print_vector(Vector *v)
{
    printf("(%f, %f, %f)\n", v->x, v->y, v->z);
}


Boolean is_left_rotate(Point *P1, Point *P2, Point *P3, Vector *normal)
{
    Vector a;
    Vector b;
    Vector verifiable_normal;

    build_vector_by_points(P1, P2, &a);
    build_vector_by_points(P2, P3, &b);

    cross_product(&a, &b, &verifiable_normal);

    return dot_product(&verifiable_normal, normal) > 0;
}


Boolean line_intersect_triangle(Line *line, Triangle *triangle)
{
    Point *P1 = &triangle->P1;
    Point *P2 = &triangle->P2;
    Point *P3 = &triangle->P3;

    Point *M0 = &line->M0;
    Point *M1 = &line->M1;

    float A = (P2->y - P1->y)*(P3->z - P1->z) - (P2->z - P1->z)*(P3->y - P1->y);
    float B = (P2->z - P1->z)*(P3->x - P1->x) - (P2->x - P1->x)*(P3->z - P1->z);
    float C = (P2->x - P1->x)*(P3->y - P1->y) - (P2->y - P1->y)*(P3->x - P1->x);
    float D = A * P1->x + B * P1->y + C * P1->z;
    float t = (D - A * M0->x - B * M0->y - C * M0->z) / ( A*(M1->x - M0->x) + B*(M1->y - M0->y) + C*(M1->z - M0->z) );

    Point intersect;

    intersect.x = (M1->x - M0->x)*t + M0->x;
    intersect.y = (M1->y - M0->y)*t + M0->y;
    intersect.z = (M1->z - M0->z)*t + M0->z;

    Vector a;
    Vector b;
    Vector c;
    Vector normal;

    build_vector_by_points(P1, P3, &a);
    build_vector_by_points(P3, P2, &b);

    cross_product(&a, &b, &normal);

    Boolean is_left = is_left_rotate(P1, P3, &intersect, &normal);

    if(is_left_rotate(P3, P2, &intersect, &normal) != is_left)
        return 0;

    if(is_left_rotate(P2, P1, &intersect, &normal) != is_left)
        return 0;

    return 1;
}
