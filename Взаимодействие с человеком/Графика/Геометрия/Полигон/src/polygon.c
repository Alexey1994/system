#include <math.h>
#include <libs/graphics/light/light.h>
#include <libs/graphics/geometry/matrix/matrix.h>
#include <GL/gl.h>


void initialize_triangle(Triangle triangle, Point *p1, Point *p2, Point *p3)
{
    triangle[0] = p1;
    triangle[1] = p2;
    triangle[2] = p3;
}


void deinitialize_triangle(Triangle triangle)
{
    destroy_point(triangle[0]);
    destroy_point(triangle[1]);
    destroy_point(triangle[2]);
}


Triangle* create_triangle(Point *p1, Point *p2, Point *p3)
{
    Triangle *triangle = new(Triangle);

    initialize_triangle(*triangle, p1, p2, p3);

    return triangle;
}


void destroy_triangle(Triangle *triangle)
{
    deinitialize_triangle(*triangle);
    free(triangle);
}


void initialize_quad(Quad quad, Point *p1, Point *p2, Point *p3, Point *p4)
{
    quad[0] = p1;
    quad[1] = p2;
    quad[2] = p3;
    quad[3] = p4;
}


void deinitialize_quad(Quad quad)
{
    destroy_point(quad[0]);
    destroy_point(quad[1]);
    destroy_point(quad[2]);
    destroy_point(quad[3]);
}


Quad* create_quad(Point *p1, Point *p2, Point *p3, Point *p4)
{
    Quad *quad = new(Quad);

    initialize_quad(*quad, p1, p2, p3, p4);

    return quad;
}


void destroy_quad(Quad *quad)
{
    deinitialize_quad(*quad);
    free(quad);
}


void draw_triangle(Triangle triangle)
{
    Point *p;
    float  color_weight;

    Vector *normal = cross_product(
        build_vector_by_points(
            triangle[0],
            triangle[1]
        ),

        build_vector_by_points(
            triangle[0],
            triangle[2]
        )
    );

    normalize_vector(normal);
    color_weight = dot_product(normal, &light) / 2.0f;

    if(color_weight<0)
        color_weight = -color_weight;
    //printf("weight %f\n", color_weight);

    glColor3f(color_weight, color_weight, color_weight);

    glBegin(GL_TRIANGLES);
        p = triangle[0];
        glVertex3f(p->coords[0], p->coords[1], p->coords[2]);

        p = triangle[1];
        glVertex3f(p->coords[0], p->coords[1], p->coords[2]);

        p = triangle[2];
        glVertex3f(p->coords[0], p->coords[1], p->coords[2]);
    glEnd();
}


Triangle* rotate_triangle(Triangle triangle, Rotate *rotate)
{
    return create_triangle(
        rotate_point(triangle[0], rotate),
        rotate_point(triangle[1], rotate),
        rotate_point(triangle[2], rotate)
    );
}


Triangle* scale_triangle(Triangle triangle, Scale *scale)
{
    return create_triangle(
        scale_point(triangle[0], scale),
        scale_point(triangle[1], scale),
        scale_point(triangle[2], scale)
    );
}


Triangle* translate_triangle(Triangle triangle, Translate *translate)
{
    return create_triangle(
        translate_point(triangle[0], translate),
        translate_point(triangle[1], translate),
        translate_point(triangle[2], translate)
    );
}
