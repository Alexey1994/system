#ifndef MATRIX_H_INCLUDED
#define MATRIX_H_INCLUDED


#include <libs/graphics/geometry/vector/vector.h>


typedef struct
{
    float *data;
    int    length_x;
    int    length_y;
}
Matrix;


void initialize_matrix(Matrix *matrix, int length_x, int length_y);

Matrix* create_matrix(int length_x, int length_y);

void initialize_3x3_matrix(
    Matrix *matrix,
    float a11, float a12, float a13,
    float a21, float a22, float a23,
    float a31, float a32, float a33
);

void deinitialize_matrix(Matrix *matrix);


Matrix* create_matrix(int length_x, int length_y);

Matrix* create_3x3_matrix(
    float a11, float a12, float a13,
    float a21, float a22, float a23,
    float a31, float a32, float a33
);

void destroy_matrix(Matrix *matrix);


float   get_matrix_value(Matrix *matrix, int position_x, int position_y);
void    set_matrix_value(Matrix *matrix, int position_x, int position_y, float value);

Vector* multiply_matrix_by_vector(Matrix *matrix, Vector *vector);
Vector* multiply_vector_by_matrix(Vector *vector, Matrix *matrix);


#include "matrix.c"

#endif // MATRIX_H_INCLUDED
