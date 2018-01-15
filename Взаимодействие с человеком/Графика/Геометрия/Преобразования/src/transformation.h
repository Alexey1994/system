#ifndef TRANSFORMATION_H_INCLUDED
#define TRANSFORMATION_H_INCLUDED


#include <libs/graphics/geometry/vector/vector.h>
#include <libs/graphics/geometry/matrix/matrix.h>


typedef struct
{
    Vector *vector;
    float   angle;
    Matrix *matrix;
}
Rotate;


void    initialize_rotate   (Rotate *rotate, float angle, Vector *vector);
void    deinitialize_rotate (Rotate *rotate);

Rotate* create_rotate       (float angle, Vector *vector);
void    destroy_rotate      (Rotate *rotate);

Point*  rotate_point(Point *point, Rotate *rotate);


typedef struct
{
    Vector *vector;
    //Matrix *matrix;
}
Scale;


void   initialize_scale   (Scale *scale, Vector *vector);
void   deinitialize_scale (Scale *scale);

Scale* create_scale       (Vector *vector);
void   destroy_scale      (Scale *scale);

Point* scale_point        (Point *point, Scale *scale);


typedef struct
{
    Vector *vector;
    //Matrix *matrix;
}
Translate;


void       initialize_translate   (Translate *translate, Vector *vector);
void       reinitialize_translate (Translate *translate, Vector *vector);
void       deinitialize_translate (Translate *translate);

Translate* create_translate       (Vector *vector);
void       destroy_translate      (Translate *translate);

Point*     translate_point        (Point *point, Translate *translate);


#include "transformation.c"

#endif // TRANSFORMATION_H_INCLUDED
