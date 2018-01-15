#include <libs/graphics/graphics.h>
#include <libs/data structures/array/array.h>

#include <libs/graphics/geometry/polygon/polygon.h>
#include <libs/graphics/light/light.h>


static float angle  = 0;


typedef struct
{
    Array *triangles;

    Translate translate;
    Rotate    rotate;
    Scale     scale;
}
Static_Object;


Static_Object* create_static_object          ();
void           destroy_static_object         (Static_Object *object);

void           add_triangle_to_static_object (Static_Object *object, Triangle *triangle);
void           draw_static_object            (Static_Object *object);


Static_Object* create_static_object()
{
    Static_Object *object = new(Static_Object);

    object->triangles = create_array(2, destroy_triangle);

    return object;
}


void destroy_static_object(Static_Object *object)
{
    destroy_array(object);
    free(object);
}


void add_triangle_to_static_object(Static_Object *object, Triangle *triangle)
{
    Triangle *new_triangle = create_triangle((*triangle)[0], (*triangle)[1], (*triangle)[2]);

    push_in_array(object->triangles, new_triangle);
}


Static_Object* copy_static_object(Static_Object *object)
{
    int i;

    Static_Object *new_object = create_static_object();

    for(i=0; i<object->triangles->length; ++i)
        add_triangle_to_static_object(new_object, object->triangles->data[i]);

    return new_object;
}


void add_quad_to_static_object(Static_Object *object, Quad *quad)
{
    Triangle *triangle;

    triangle = create_triangle((*quad)[0], (*quad)[1], (*quad)[2]);
    push_in_array(object->triangles, triangle);

    triangle = create_triangle((*quad)[0], (*quad)[2], (*quad)[3]);
    push_in_array(object->triangles, triangle);
}


void translate_static_object(Static_Object *object, Translate *translate)
{
    int i;

    for(i=0; i<object->triangles->length; ++i)
    {
        Triangle *triangle = object->triangles->data[i];
        object->triangles->data[i] = translate_triangle(*triangle, translate);
    }
}


void rotate_static_object(Static_Object *object, Rotate *rotate)
{
    int i;

    for(i=0; i<object->triangles->length; ++i)
    {
        Triangle *triangle = object->triangles->data[i];
        object->triangles->data[i] = rotate_triangle(*triangle, rotate);
    }
}


void scale_static_object(Static_Object *object, Scale *scale)
{
    int i;

    for(i=0; i<object->triangles->length; ++i)
    {
        Triangle *triangle = object->triangles->data[i];
        object->triangles->data[i] = scale_triangle(*triangle, scale);
    }
}


void draw_static_object(Static_Object *object)
{
    int i;

    for(i=0; i<object->triangles->length; ++i)
    {
        Triangle *triangle = object->triangles->data[i];

        draw_triangle(*triangle);
    }
}


typedef struct
{
    unsigned int   start_time;
    unsigned int   end_time;
    unsigned int   current_time;

    Rotate         new_rotate;
    Translate      new_translate;

    Rotate         rotate;
    Translate      translate;
    void         (*translate_triangle)(struct Animation_Time *time, Triangle *triangle);
    void         (*rotate_triangle)(struct Animation_Time *time, Triangle *triangle);
}
Animation_Time;


void initialize_animation_time(Animation_Time *time, Vector *rotate_vector)
{
    //Vector *rotate_vector = create_3D_point(0, 1, 1);
    //normalize_vector(rotate_vector);

    initialize_rotate(&time->rotate, 0, rotate_vector);
    initialize_translate(&time->translate, create_3D_point(0, 0, 0));
}


typedef struct
{
    Static_Object  *object;
    Static_Object  *new_object;
    Animation_Time  time;

    Point          *start_point_next_nodes;
    Point          *new_start_point_next_nodes;
    Array          *next_nodes;
/*
    Point          *start_point;
    Point          *end_point;

    Point          *new_start_point;
    Point          *new_end_point;*/
}
Animation_Node;


void initialize_animation_node(Animation_Node *node, Static_Object *object, Point *start_point_next_nodes)
{
    node->object = object;
    //node->new_object = copy_static_object(object);

    node->next_nodes = create_array(4, 0);
    node->start_point_next_nodes = start_point_next_nodes;
}


void deinitialize_animation_node(Animation_Node *node)
{

}


Animation_Node* create_animation_node(Static_Object *object, Point *start_point_next_nodes)
{

}


void add_animation_node(Animation_Node *parent_node, Animation_Node *new_node)
{
    push_in_array(parent_node->next_nodes, new_node);
}


void destroy_animation_node(Animation_Node *node)
{
    deinitialize_animation_node(node);
    free(node);
}


void init_new_object(Animation_Node *node)
{
    int i;

    node->new_object = copy_static_object(node->object);
    node->new_start_point_next_nodes = create_3D_point(node->start_point_next_nodes->coords[0], node->start_point_next_nodes->coords[1], node->start_point_next_nodes->coords[2]);
    initialize_rotate(&node->time.new_rotate, node->time.rotate.angle, node->time.rotate.vector);

    //node->new_start_point_next_nodes = 0;
    //initialize_translate(&node->time.new_translate, node->start_point_next_nodes);
    //initialize_rotate(&node->time.new_rotate, 0, node->time.rotate.vector);

    //initialize_rotate(&node->time.new_rotate, 0, create_3D_point(1, 0, 0));

    for(i=0; i<node->next_nodes->length; ++i)
    {
        Animation_Node *next_node = node->next_nodes->data[i];
        init_new_object(next_node);
    }
}


void rotate_childs_animation(Animation_Node *node, Rotate *rotate)
{
    int     i;
    Vector *new_rotate_vector;
    float   new_rotate_angle;

    new_rotate_vector = rotate_point(node->time.new_rotate.vector, rotate);
    new_rotate_angle  = angle/180.0f;

    initialize_rotate(&node->time.new_rotate, new_rotate_angle, new_rotate_vector);
    rotate_static_object(node->new_object, rotate);
    node->new_start_point_next_nodes = rotate_point(node->new_start_point_next_nodes, rotate);

    for(i=0; i<node->next_nodes->length; ++i)
    {
        Animation_Node *next_node = node->next_nodes->data[i];
        rotate_childs_animation(next_node, rotate);
    }
}


void translate_child_objects(Animation_Node *node, Translate *translate)
{
    int i;

    translate_static_object(node->new_object, translate);

    for(i=0; i<node->next_nodes->length; ++i)
    {
        Animation_Node *next_node = node->next_nodes->data[i];
        translate_child_objects(next_node, translate);
    }
}


void translate_childs_animation(
    Animation_Node *node,
    Animation_Node *previouse_node, //start point
    Rotate *rotate)
{
    int i;

    if(previouse_node)
    {
        initialize_translate(&node->time.new_translate, previouse_node->new_start_point_next_nodes);
        translate_child_objects(node, &node->time.new_translate);
    }
}


void play_animation(Animation_Node *node, Animation_Node *previouse_node)
{
    int             i;
    Animation_Node *next_node;

    Vector *new_translate_vector;
    Vector *new_rotate_vector;

    //node->time.rotate.angle = angle/180.0f;

    if(!previouse_node)
        init_new_object(node);

    Rotate current_rotate;
    if(previouse_node)
        initialize_rotate(&current_rotate, 1, node->time.new_rotate.vector);
    else
        initialize_rotate(&current_rotate, angle/180.0f, node->time.new_rotate.vector);

    rotate_childs_animation(node, &current_rotate);
    translate_childs_animation(node, previouse_node, &current_rotate);

    scale_static_object(node->new_object, create_scale(create_3D_point( 900.0f/1440.0f, 1, 1 )));
    draw_static_object(node->new_object);

    for(i=0; i<node->next_nodes->length; ++i)
    {
        next_node = node->next_nodes->data[i];

        play_animation(next_node, node);
    }
}


typedef struct
{
    Array *teils;
    Array *teil_links;
}
Animation;


void draw_animation(Animation *animation)
{

}


void draw_scene()
{
    static Static_Object *object = 0;
    static Animation_Node animation;
    static Animation_Node next_animation;
    static Animation_Node next_animation2;
    static Animation_Node next_animation3;
    static Animation_Node next_animation4;
    static Animation_Node next_animation5;
    static Animation_Node next_animation6;
    static Animation_Node next_animation7;
    //static float          angle  = 0;
//glEnable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);

    if(!object)
    {
        object = create_static_object();

        add_quad_to_static_object(
            object,
            create_quad(
                create_3D_point(0,   0,   0),
                create_3D_point(0,   0.1, 0),
                create_3D_point(0.1, 0.1, 0),
                create_3D_point(0.1, 0,   0)
            )
        );

        add_quad_to_static_object(
            object,
            create_quad(
                create_3D_point(0,   0,   0.1),
                create_3D_point(0.1, 0,   0.1),
                create_3D_point(0.1, 0.1, 0.1),
                create_3D_point(0,   0.1, 0.1)
            )
        );

        add_quad_to_static_object(
            object,
            create_quad(
                create_3D_point(0,   0, 0),
                create_3D_point(0.1, 0, 0),
                create_3D_point(0.1, 0, 0.1),
                create_3D_point(0,   0, 0.1)
            )
        );

        add_quad_to_static_object(
            object,
            create_quad(
                create_3D_point(0,  0.1, 0),
                create_3D_point(0,  0.1,  0.1),
                create_3D_point( 0.1,  0.1,  0.1),
                create_3D_point( 0.1,  0.1, 0)
            )
        );

        add_quad_to_static_object(
            object,
            create_quad(
                create_3D_point( 0.1, 0, 0),
                create_3D_point( 0.1,  0.1, 0),
                create_3D_point( 0.1,  0.1,  0.1),
                create_3D_point( 0.1, 0,  0.1)
            )
        );

        add_quad_to_static_object(
            object,
            create_quad(
                create_3D_point(0, 0, 0),
                create_3D_point(0, 0,  0.1),
                create_3D_point(0,  0.1,  0.1),
                create_3D_point(0,  0.1, 0)
            )
        );

        //initialize_translate(&object->translate, create_3D_point(0.1, 0.1, 0.1));
        //initialize_rotate(&object->rotate, 0, create_3D_point(1, 0, 1));
        //initialize_scale(&object->scale, create_3D_point(900.0f/1440.0f, 1, 1));


        initialize_animation_node(&animation, object, create_3D_point(0.1, 0, 0));
        Vector *rotate_vector = create_3D_point(1, 1, 1);
        normalize_vector(rotate_vector);
        initialize_animation_time(&animation.time, rotate_vector);

        initialize_animation_node(&next_animation, object, create_3D_point(0.1, 0, 0));
        rotate_vector = create_3D_point(0, 1, 0);
        normalize_vector(rotate_vector);
        initialize_animation_time(&next_animation.time, rotate_vector);

        add_animation_node(&animation, &next_animation);

        initialize_animation_node(&next_animation2, object, create_3D_point(0.1, 0, 0));
        rotate_vector = create_3D_point(0, 0, 1);
        normalize_vector(rotate_vector);
        initialize_animation_time(&next_animation2.time, rotate_vector);

        add_animation_node(&next_animation, &next_animation2);

        initialize_animation_node(&next_animation3, object, create_3D_point(0.1, 0, 0));
        rotate_vector = create_3D_point(0, 1, 0);
        normalize_vector(rotate_vector);
        initialize_animation_time(&next_animation3.time, rotate_vector);

        //add_animation_node(&next_animation2, &next_animation3);

        initialize_animation_node(&next_animation3, object, create_3D_point(0.1, 0, 0));
        rotate_vector = create_3D_point(0, 1, 0);
        normalize_vector(rotate_vector);
        initialize_animation_time(&next_animation3.time, rotate_vector);

        //add_animation_node(&next_animation2, &next_animation3);
/*
        initialize_animation_node(&next_animation4, object, create_3D_point(0.1, 0, 0));
        rotate_vector = create_3D_point(1, 1, 1);
        normalize_vector(rotate_vector);
        initialize_animation_time(&next_animation4.time, rotate_vector);

        add_animation_node(&next_animation3, &next_animation4);

        initialize_animation_node(&next_animation5, object, create_3D_point(0.1, 0, 0));
        rotate_vector = create_3D_point(1, 1, 1);
        normalize_vector(rotate_vector);
        initialize_animation_time(&next_animation5.time, rotate_vector);

        add_animation_node(&next_animation4, &next_animation5);

        initialize_animation_node(&next_animation6, object, create_3D_point(0.1, 0, 0));
        rotate_vector = create_3D_point(1, 1, 1);
        normalize_vector(rotate_vector);
        initialize_animation_time(&next_animation6.time, rotate_vector);

        add_animation_node(&next_animation5, &next_animation6);

        initialize_animation_node(&next_animation7, object, create_3D_point(0.1, 0, 0));
        rotate_vector = create_3D_point(1, 1, 1);
        normalize_vector(rotate_vector);
        initialize_animation_time(&next_animation7.time, rotate_vector);

        add_animation_node(&next_animation6, &next_animation7);*/
    }

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glColor3f(0,0,0);

    Vector *rotate_vector = create_3D_point(0, 1, 1);
    normalize_vector(rotate_vector);
    initialize_rotate(&object->rotate, angle/180, rotate_vector);
    //draw_static_object(object);

    play_animation(&animation, 0);
    printf("\n");

    ++angle;
}


int main()
{
    initialize_light();
    set_light_position(1, 1, 1);

    init_graphics(1440, 900, 100, draw_scene);

    for(;;)
    {
        sleep_thread(1);
    }

    return 0;
}
