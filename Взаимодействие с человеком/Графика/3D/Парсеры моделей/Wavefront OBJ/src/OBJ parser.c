typedef struct
{
    N_32 vertex_index;
    N_32 texture_coord_index;
    N_32 normal_index;
}
Polygon_Point_Index;


private procedure read_polygon_point_index_component(N_32 *component, Input *input)
{
    *component = read_N_32(input);

    if(input->head == '/')
        read_byte(input);
}


private procedure read_OBJ_polygon(Object *object, Input *input)
{
    Array               *polygon;
    Polygon_Point_Index *index;

    polygon = create_array(1, &free);

    do
    {
        index = new(Polygon_Point_Index);
        skip_input_spaces(input);

        read_polygon_point_index_component(&index->vertex_index, input);
        read_polygon_point_index_component(&index->texture_coord_index, input);
        read_polygon_point_index_component(&index->normal_index, input); //index->normal_index = read_N_32(input);

        add_in_array(polygon, index);
        printf(" %d/%d/%d", index->vertex_index, index->texture_coord_index, index->normal_index);
    }
    while(!end_of_input(input) && input->head != '\r' && input->head != '\n');

    add_in_array(&object->polygons, polygon);
}


private function Point_3D* read_OBJ_point(Input *input, N_32 dimension)
{
    Point *point;
    N_32   i;

    point = new(Point_3D);
    point->length = dimension;

    for(i=0; i<dimension; ++i)
    {
        skip_input_spaces(input);
        point->coords[i] = read_R_32(input);
    }

    return point;
}


function Boolean parse_OBJ(StaticModel *model, Input *input, procedure (*initialize_input)(Input *input, Byte *path))
{
    Object *object;
    Point  *point;
    Array   vertieces;
    Array   normals;
    Array   texture_coords;
    Array   indexes;

    object = new(Object);

    initialize_array(&object->polygons, 2, &destroy_array);

    initialize_array(&vertieces, 2, &free);
    initialize_array(&normals, 2, &free);
    initialize_array(&texture_coords, 2, &free);
    initialize_array(&indexes, 2, &free);

    while(!end_of_input(input))
    {
        if(input->head == '#')
            skip_input_text_empty_lines(input);
        else if(read_if_next(input, "f "))
        {
            printf("f");
            read_OBJ_polygon(object, input);
        }
        else if(read_if_next(input, "v "))
        {
            point = read_OBJ_point(input, 3);
            add_in_array(&vertieces, point);
            printf("v %f %f %f\n", point->coords[0], point->coords[1], point->coords[2]);
        }
        else if(read_if_next(input, "vt "))
        {
            point = read_OBJ_point(input, 2);
            add_in_array(&texture_coords, point);
            printf("vt %f %f\n", point->coords[0], point->coords[1]);
        }
        else if(read_if_next(input, "vn "))
        {
            point = read_OBJ_point(input, 3);
            add_in_array(&normals, point);
            printf("vn %f %f %f\n", point->coords[0], point->coords[1], point->coords[2]);
        }

        skip_input_text_empty_lines(input);
    }

    return 1;

error:
    return 0;
}
