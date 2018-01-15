#include <stdio.h>
#include <GL/gl.h>
#include "TTF.h"
#include <libs/graphics/graphics.h>
#include <libs/input/input.h>

#include "combinatorics.h"
#include "geometry.h"


void put_file_byte(FILE *file_out, Byte byte)
{
    fputc(byte, file_out);
}


void print(int *textures, TTF *ttf, Byte *text)
{
    float width;

    float x = 0;

    glColor3f(0,0,0);

    for(; *text; ++text)
    {
        if(*text == ' ')
        {
            x += (float)ttf->glyphs[ 0 ]->max_x / 900.0f*0.022;
            continue;
        }

        width = (float)ttf->glyphs[ *text - 32 ]->max_x / 900.0f*0.022;

        glBindTexture(GL_TEXTURE_2D, textures[*text - 32]);

        glBegin(GL_QUADS);
            glTexCoord2f(0, 0); glVertex2f(x, 0);
            glTexCoord2f(1, 0); glVertex2f(x + 0.05, 0);
            glTexCoord2f(1, 1); glVertex2f(x + 0.05, 0.05);
            glTexCoord2f(0, 1); glVertex2f(x, 0.05);
        glEnd();

        //x+=0.05;
        x += width;
    }
}


void draw()
{
    static TTF         *ttf = 0;
    static BezierCurve *curve;
    static Canvas      *glyph_canvas;
    static int          textures[64];

    int i;

    if(!ttf)
    {
        FILE   *file_in       = fopen("a.ttf", "rb");
        Stream *input_stream  = create_stream(file_in, fgetc, feof);

        ttf = load_TTF(input_stream);

        fclose(file_in);

        glyph_canvas = create_canvas(128, 128, 4);
        //rasterize_glyph(ttf->glyphs[14], glyph_canvas);

        //rasterize_line(0, 0, 0.5, 0.5, glyph_canvas);
        //rasterize_line(0.5, 0.5, 0.5, 0.8, glyph_canvas);
        //rasterize_line(0.5, 0.5, 0.8, 0.5, glyph_canvas);
        //rasterize_line(0.0, 0.0, 0.8, 0.1, glyph_canvas);

        Point2D *points = create_points(3);

        points[0].x = 0;
        points[0].y = 0;

        points[1].x = 0.5;
        points[1].y = 0.5;

        points[2].x = 1;
        points[2].y = 0;

        curve = create_Bezier_curve(points, 3);

        //rasterize_Bezier_curve(curve, glyph_canvas);

        for(i=0; i<90; ++i)
        //i = '8' - 32;
        {
            clear_canvas(glyph_canvas);
            rasterize_glyph(ttf->glyphs[i], glyph_canvas);
            textures[i] = create_texture(glyph_canvas);
        }
    }
//rasterize_glyph(ttf->glyphs[5], glyph_canvas);


    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();

    glColor3f(0,0,0);
    //print_TTF("@1234567890", ttf);

    float scale = 1;

    static int k=0;

    if(key_down('A') && k)
        --k;

    if(key_down('S') && k<90)
        ++k;

    glEnable(GL_TEXTURE_2D);
    glColor3f(0, 0, 0);
    glBindTexture(GL_TEXTURE_2D, textures[k]);

    //glBegin(GL_QUADS);
        //glTexCoord2f(0, 0); glVertex2f(0, 0);
        //glTexCoord2f(1, 0); glVertex2f(scale, 0);
        //glTexCoord2f(1, 1); glVertex2f(scale, scale);
        //glTexCoord2f(0, 1); glVertex2f(0, scale);
    //glEnd();

    print(textures, ttf, "Fill with a glyph canvas");
}


int main()
{
    init_graphics(1440, 900, 60, draw);

    for(;;){}

    return 0;
}

