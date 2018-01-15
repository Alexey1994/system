#ifndef STATIC_MODEL_H_INCLUDED
#define STATIC_MODEL_H_INCLUDED

typedef struct
{
    float        *vertieces;
    unsigned int  length_vertieces;

    float        *normals;
    unsigned int  length_normals;

    unsigned int *indexes;
    unsigned int  length_indexes;
}
Object;


void draw_object(Object *object);

#endif // STATIC_MODEL_H_INCLUDED
