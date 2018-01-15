int main()
{
    Triangle triangle;

    initialize_triangle(triangle,
        create_3D_point(0, 1, 2),
        create_3D_point(3, 4, 5),
        create_3D_point(6, 7, 8)
    );

    printf("%f %f %f\n", triangle[0]->coords[0], triangle[0]->coords[1], triangle[0]->coords[2]);

    return 0;
}
