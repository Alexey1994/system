#include "geometry.h"
#include "combinatorics.h"
#include <libs/extends/extends.h>

#include <math.h>
#include <GL/gl.h>


Canvas* create_canvas(int width, int height, int bytes_per_pixel)
{
    int i;

    Canvas *canvas = new(Canvas);

    canvas->width           = width;
    canvas->height          = height;
    canvas->bytes_per_pixel = bytes_per_pixel;
    canvas->data            = new_array(Byte, width * height * bytes_per_pixel);

    for(i=0; i<width * height * bytes_per_pixel; ++i)
        canvas->data[i] = 0;

    return canvas;
}


void destroy_canvas(Canvas *canvas)
{
    free(canvas->data);
    free(canvas);
}


void clear_canvas(Canvas *canvas)
{
    int i;

    for(i=0; i<canvas->width * canvas->height * canvas->bytes_per_pixel; ++i)
        canvas->data[i] = 0;
}


Canvas* copy_canvas(Canvas *canvas)
{
    int i;

    Canvas *new_canvas = create_canvas(canvas->width, canvas->height, canvas->bytes_per_pixel);

    for(i=0; i<new_canvas->width * new_canvas->height * new_canvas->bytes_per_pixel; ++i)
        new_canvas->data[i] = canvas->data[i];

    return new_canvas;
}


int create_texture(Canvas *canvas)
{
    int texture;

    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexImage2D(GL_TEXTURE_2D, 0, 4, canvas->width, canvas->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, canvas->data);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

    return texture;
}


Byte* get_pixel(Canvas *canvas, int x, int y)
{
    return canvas->data + (y*canvas->width + x) * canvas->bytes_per_pixel;
}


static Byte is_angle(Canvas *canvas, int x, int y)
{
    int  dx;
    Byte is_angle = 1;

    if(y<=0 || y>=canvas->height)
        return 0;

    if(x<=1 || x>=canvas->width-1)
        return 0;

    for(dx=x; dx<canvas->width && get_pixel(canvas, dx, y)[3]; ++dx)
        if(get_pixel(canvas, dx, y-1)[3])
        {
            is_angle = 0;
            break;
        }

    if(dx<canvas->width && get_pixel(canvas, dx, y-1)[3])
        is_angle = 0;

    if(x && get_pixel(canvas, x-1, y-1)[3])
        is_angle = 0;

    if(is_angle)
        return 1;

    for(dx=x; dx<canvas->width && get_pixel(canvas, dx, y)[3]; ++dx)
        if(get_pixel(canvas, dx, y+1)[3])
            return 0;

    if(dx<canvas->width && get_pixel(canvas, dx, y+1)[3])
        return 0;

    if(x && get_pixel(canvas, x-1, y+1)[3])
        return 0;

    return 1;
}


void fill_contours(Canvas *canvas)
{int t = 0;
    int  x;
    int  y;
    Byte pixel;
    Byte is_inline;
    Byte is_fill;

    Canvas *copy = copy_canvas(canvas);

    for(y=0; y<canvas->height; ++y)
    {
        is_inline = 0;
        is_fill = 0;

        x=0;

        while(x<canvas->width)
        {
            for(; x<canvas->width && !get_pixel(canvas, x, y)[3]; ++x);

            do
            {
                if(is_angle(copy, x, y))
                {++t;
                    is_inline = 0;

                    get_pixel(canvas, x, y)[0] = 100;
                    get_pixel(canvas, x, y)[1] = 0;
                    get_pixel(canvas, x, y)[2] = 0;
                    get_pixel(canvas, x, y)[3] = 100;
                }
                else
                {
                    is_inline = 1;
                    is_fill = !is_fill;
                }

                for(; x<canvas->width && get_pixel(canvas, x, y)[3]; ++x);

                for(; x<canvas->width && !get_pixel(canvas, x, y)[3]; ++x)
                    if(is_fill)
                    {/*
                        get_pixel(canvas, x, y)[0] = 255;
                        get_pixel(canvas, x, y)[1] = 255;
                        get_pixel(canvas, x, y)[2] = 255;
                        get_pixel(canvas, x, y)[3] = 255;*/
                    }
                    else
                    {/*
                        get_pixel(canvas, x, y)[0] = 255;
                        get_pixel(canvas, x, y)[1] = 255;
                        get_pixel(canvas, x, y)[2] = 255;*/
                    }
            }
            while(!is_inline && x<canvas->width);

            for(; x<canvas->width && get_pixel(canvas, x, y)[3]; ++x);

            is_fill = 0;
        }
    }

    printf("%d\n", t);
}


Point2D* create_points(int length)
{
    return new_array(Point2D, length);
}


void destroy_points(Point2D *points)
{
    free(points);
}


BezierCurve* create_Bezier_curve(Point2D *points, int length)
{
    int i;

    BezierCurve *curve = new(BezierCurve);

    curve->points       = points;
    curve->length       = length;
    curve->coefficients = new_array(float, length);

    for(i=0; i<length; ++i)
        curve->coefficients[i] = C(length-1, i);

    return curve;
}


void destroy_Bezier_curve(BezierCurve *curve)
{
    free(curve->points);
    free(curve);
}


//static float


void draw_Bezier_curve(BezierCurve *curve)
{
    int   i;
    float t;
    float one_minus_t;
    float x1;
    float y1;
    float x2;
    float y2;
    float coefficient;

    float step = 0.1;

    glBegin(GL_LINE_STRIP);

        for(t = 0; t < 1.0; t += step)
        {
            one_minus_t = 1.0f - t;

            x1 = 0;
            y1 = 0;

            for(i=0; i<curve->length; ++i)
            {
                coefficient = real_power(t, i) * real_power(one_minus_t, curve->length - i - 1) * curve->coefficients[i];

                x1 += coefficient * curve->points[i].x;
                y1 += coefficient * curve->points[i].y;
            }

            one_minus_t = 1.0f - t - step;
            x2 = 0;
            y2 = 0;

            for(i=0; i<curve->length; ++i)
            {
                coefficient = real_power(t+step, i) * real_power(one_minus_t, curve->length - i - 1) * curve->coefficients[i];

                x2 += coefficient * curve->points[i].x;
                y2 += coefficient * curve->points[i].y;
            }

            //glVertex2f(x, y);
            draw_line(x1 * 1440, y1 * 900, x2 * 1440, y2 * 900);
        }



        //glVertex2f(curve->points[curve->length-1].x, curve->points[curve->length-1].y);

    glEnd();

    glPointSize(2);
/*
    glBegin(GL_POINTS);
        glColor3f(0.0, 0.8, 0.0);

        for(i=1; i<curve->length-1; ++i)
            glVertex2f(curve->points[i].x, curve->points[i].y);

        glColor3f(0.8, 0.0, 0.0);
        glVertex2f(curve->points[0].x, curve->points[0].y);
        glVertex2f(curve->points[i].x, curve->points[i].y);
    glEnd();*/
}


void rasterize_Bezier_curve(BezierCurve *curve, Canvas *canvas)
{
    int   i;
    float t;
    float one_minus_t;
    float x1;
    float y1;
    float x2;
    float y2;
    float coefficient;

    float step = 0.01;
    for(t = 0; t < 1.0; t += step)
    {
        one_minus_t = 1.0f - t;

        x1 = 0;
        y1 = 0;

        for(i=0; i<curve->length; ++i)
        {
            coefficient = real_power(t, i) * real_power(one_minus_t, curve->length - i - 1) * curve->coefficients[i];

            x1 += coefficient * curve->points[i].x;
            y1 += coefficient * curve->points[i].y;
        }

        if(t + step > 1.0f)
            t=1.0f-step;

        one_minus_t = 1.0f - t - step;
        x2 = 0;
        y2 = 0;

        for(i=0; i<curve->length; ++i)
        {
            coefficient = real_power(t+step, i) * real_power(one_minus_t, curve->length - i - 1) * curve->coefficients[i];

            x2 += coefficient * curve->points[i].x;
            y2 += coefficient * curve->points[i].y;
        }

        rasterize_line(x1/3.0f+0.2f, y1/3.0f+0.2f, x2/3.0f+0.2f, y2/3.0f+0.2f, canvas);
    }
}


void draw_line(float x1, float y1, float x2, float y2)
{/*
    float   t;
    float   x;
    float   y;
    Point2D l;

    float step = 0.01;

    l.x = x2 - x1;
    l.y = y2 - y1;

    step = 0.01;//1.0f/2.0f/1440.0f /sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );

    glPointSize(1);
    glBegin(GL_POINTS);

    for(t=0; t<1; t+=step)
    {
        x = x1 + l.x*t;
        y = y1 + l.y*t;
//printf("%f %f\n", x, y);
        glVertex2f(x, y);
    }

    glEnd();*/
}


void rasterize_line(float x1, float y1, float x2, float y2, Canvas *canvas)
{//draw_line(x1, y1, x2, y2); return;
    float   t;
    int     x;
    int     y;
    Point2D l;

    float step;

    x1*=canvas->width;
    x2*=canvas->width;
    y1*=canvas->height;
    y2*=canvas->height;

    l.x = x2 - x1;
    l.y = y2 - y1;

    float line_length = sqrt( (x2-x1)*(x2-x1) + (y2-y1)*(y2-y1) );

    if(line_length)
        step = 1.0f/line_length;
    else
        step = 0.0001;

    for(t=0.0f; t<1.0f; t+=step)
    {
        x = x1 + l.x*t;
        y = y1 + l.y*t;

        if(x>=0 && y>=0 && x < canvas->width && y < canvas->height)
            canvas->data[ (y*canvas->width + x) * canvas->bytes_per_pixel + 3 ] = 255;
    }
/*
    x = x1 + l.x;
    y = y1 + l.y;

    if(x>=0 && y>=0 && x < canvas->width && y < canvas->height)
        canvas->data[ ((int)y*canvas->width + (int)x) * canvas->bytes_per_pixel ] = 1;*/

}
