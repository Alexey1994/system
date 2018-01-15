#include <stdio.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include "extends.h"
#include "lib/graphics.h"
#include "lib/static model.h"
#include "lib/input.h"
#include "translates.h"
#include "geometry.h"
#include <math.h>


static float   x      = -1;
static float   y      = 0;
static float   z      = 0;


FILE* open_file(Byte *file_name)
{
    return fopen(file_name, "rb");
}


void set_lighting()
{
    glLightModelf(GL_LIGHT_MODEL_TWO_SIDE, GL_TRUE);

    float diffuse_color[]  = {0.6, 0.6, 0.6, 1};
    float specular_color[] = {1, 0.6, 0.6, 1};
    float ambient_color[]  = {0.1, 0.1, 0.1, 0};
    float light_position[] = {0.0, 0.0, 10.0, 1};

    glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, specular_color);
    glLightfv(GL_LIGHT0, GL_AMBIENT, ambient_color);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
}


void draw_intersect(float x1, float y1, float z1, float x2, float y2, float z2, float x3, float y3, float z3)
{
    Triangle triangle;
    Line     line;

    triangle.P1.x = -x1;
    triangle.P1.y = y1;
    triangle.P1.z = -z1;

    triangle.P2.x = -x2;
    triangle.P2.y = y2;
    triangle.P2.z = -z2;

    triangle.P3.x = -x3;
    triangle.P3.y = y3;
    triangle.P3.z = -z3;

    line.M0.x = x;
    line.M0.y = y;
    line.M0.z = z;

    line.M1.x = x + sin(mouse_coord_x * 90 * M_PI/180.0f);
    line.M1.y = y + sin(mouse_coord_y * 90 * M_PI/180.0f);
    line.M1.z = z + cos(mouse_coord_x * 90 * M_PI/180.0f);

    if(line_intersect_triangle(&line, &triangle))
        glColor3f(1,0,0);
    else
        glColor3f(0,0,0);

    glBegin(GL_TRIANGLES);
        glVertex3f(x1, y1, z1);
        glVertex3f(x2, y2, z2);
        glVertex3f(x3, y3, z3);
    glEnd();
}


void draw()
{
    static Object *object = 0;

    glDisable(GL_DEPTH_TEST);

    if(!object)
        object = parse_OBJ("a.obj", open_file, fclose, fgetc, feof);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glDisable(GL_DEPTH_TEST);
    glDisable(GL_LIGHTING);
    glColor3f(0,0,1);
    glBegin(GL_LINES);
        glVertex2f(-0.1, 0);
        glVertex2f( 0.1, 0);
        glVertex2f(0, -0.1);
        glVertex2f(0,  0.1);
    glEnd();

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.0f, -1.0, 1.0, 400.0);
    glMatrixMode(GL_MODELVIEW);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    set_lighting();
/*
    glPushMatrix();
        glRotatef(80, 0, 1, 0);
        glTranslatef(2.4, -1, -2);
        glColor3f(1,1,0);
        draw_object(object);
    glPopMatrix();
*/
    actor(&x, &y, &z, mouse_coord_x * 90, mouse_coord_y * 90);

    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    set_lighting();
    glColor3f(1,1,0);
    //draw_object(object);

    int i;

    glEnable(GL_COLOR_MATERIAL);

    for(i=0; i<object->length_vertieces * 3; i += 9)
    {
        float *vertex1 = object->vertieces + i;
        float *vertex2 = object->vertieces + i+3;
        float *vertex3 = object->vertieces + i+6;

        draw_intersect(vertex1[0], vertex1[1], vertex1[2],  vertex2[0], vertex2[1], vertex2[2],  vertex3[0], vertex3[1], vertex3[2]);
    }

    //printf("%d\n", object->length_vertieces);
}


int main()
{
    init_graphics(1440, 900, 60, draw);
    start_mouse_coords_update(1440, 900);

    //glMatrixMode(GL_PROJECTION);
    //gluPerspective(60.0f, 1.0, 1.0, 400.0);

    glDepthFunc(GL_ALWAYS);
    //glClearDepth(1.0);

    for(;;){}

    return 0;
}

