#include <libs/extends/extends.h>


void initialize_matrix(Matrix *matrix, int length_x, int length_y)
{
    matrix->length_x = length_x;
    matrix->length_y = length_y;
    matrix->data     = new_array(float, length_x*length_y);
}


void initialize_3x3_matrix(
    Matrix *matrix,
    float a11, float a12, float a13,
    float a21, float a22, float a23,
    float a31, float a32, float a33
)
{
    initialize_matrix(matrix, 3, 3);

    matrix->data[0] = a11;
    matrix->data[1] = a12;
    matrix->data[2] = a13;

    matrix->data[3] = a21;
    matrix->data[4] = a22;
    matrix->data[5] = a23;

    matrix->data[6] = a31;
    matrix->data[7] = a32;
    matrix->data[8] = a33;
}


void deinitialize_matrix(Matrix *matrix)
{
    free(matrix->data);
}


Matrix* create_matrix(int length_x, int length_y)
{
    Matrix *matrix = new(Matrix);

    initialize_matrix(matrix, length_x, length_y);

    return matrix;
}


Matrix* create_3x3_matrix(
    float a11, float a12, float a13,
    float a21, float a22, float a23,
    float a31, float a32, float a33
)
{
    Matrix *matrix = new(Matrix);

    initialize_3x3_matrix(
        matrix,
        a11, a12, a13,
        a21, a22, a23,
        a31, a32, a33
    );

    return matrix;
}


void destroy_matrix(Matrix *matrix)
{
    deinitialize_matrix(matrix);
    free(matrix);
}


float get_matrix_value(Matrix *matrix, int position_x, int position_y)
{
    return matrix->data[position_y*matrix->length_x + position_x];
}


void set_matrix_value(Matrix *matrix, int position_x, int position_y, float value)
{
    matrix->data[position_y*matrix->length_x + position_x] = value;
}


Vector* multiply_matrix_by_vector(Matrix *matrix, Vector *vector)
{
    int i;
    int j;

    Vector *result = create_point(vector->length);

    for(i=0; i<matrix->length_y; ++i)
    {
        result->coords[i] = 0;

        for(j=0; j<matrix->length_x; ++j)
            result->coords[i] += get_matrix_value(matrix, j, i) * vector->coords[j];
    }

    return result;
}


Vector* multiply_vector_by_matrix(Vector *vector, Matrix *matrix)
{
    int i;
    int j;

    Vector *result = create_point(vector->length);

    for(i=0; i<matrix->length_x; ++i)
    {
        result->coords[i] = 0;

        for(j=0; j<matrix->length_y; ++j)
            result->coords[i] += get_matrix_value(matrix, i, j) * vector->coords[j];
    }

    return result;
}


float calculate_determinant(Matrix *matrix)
{
    if(matrix->length_x == 1)
        return matrix->data[0];

    if(matrix->length_x == 2)
        return matrix->data[0]*matrix->data[3] - matrix->data[1]*matrix->data[2];

    //for n size
}
