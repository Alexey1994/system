#include "TTF.h"

#include <libs/graphics/graphics.h>
#include <GL/gl.h>

#define SHORT_X       0b00000010
#define SHORT_Y       0b00000100
#define X_IS_SAME     0b00010000
#define Y_IS_SAME     0b00100000
#define X_IS_POSITIVE 0b00010000
#define Y_IS_POSITIVE 0b00100000
#define REPEAT_FLAG   0b00001000


static short read_number_of_contours(Stream *in)
{
    short num;

    Byte *iterator = &num;

    iterator[1] = in->head;
    get_stream_byte(in);
    iterator[0] = in->head;

    if(num)
        get_stream_byte(in);
    else
        return get_bin_stream_short(in);

    return num;
}


static Glyph* read_glyph(Stream *in)
{
    Glyph *glyph = new(Glyph);

    int i;
    int j;

    short number_of_contours = read_number_of_contours(in);

    if(!number_of_contours)
    {
        printf("glyph not defined\n");
        return 0;
    }

    short x_min              = get_bin_stream_ushort(in);
    short y_min              = get_bin_stream_ushort(in);
    short x_max              = get_bin_stream_ushort(in);
    short y_max              = get_bin_stream_ushort(in);

    short number_of_points;

    unsigned short *last_point_numbers;
    unsigned short  instruction_length;
    Byte           *flags;
    short          *coords;

    short previouse_x      = 0;
    short previouse_y      = 0;
    short previouse_real_x = 0;
    short previouse_real_y = 0;

    glyph->min_x = x_min;
    glyph->min_y = y_min;
    glyph->max_x = x_max;
    glyph->max_y = y_max;

    glyph->contours           = new_array(Contour, number_of_contours);
    glyph->number_of_contours = number_of_contours;
/*
    printf("\n\n*********** Glyph Head ****************\n\n");

    printf("number of contours %d\n", number_of_contours);
    printf("x min %d\n", x_min);
    printf("y min %d\n", y_min);
    printf("x max %d\n", x_max);
    printf("y max %d\n", y_max);
*/
    if(number_of_contours < 0)
    {
        printf("this is tailed glyph\n");
        return;
    }

    last_point_numbers = new_array(short, number_of_contours);

    for(i=0; i<number_of_contours; ++i)
    {
        last_point_numbers[i] = get_bin_stream_ushort(in);
        //printf("%d point %d\n", i, last_point_numbers[i]);
    }

    number_of_points = last_point_numbers[ number_of_contours-1 ] + 1;
    //printf("%d points\n", number_of_points);

    instruction_length = get_bin_stream_ushort(in);
    //printf("instruction length %d\n", instruction_length);

    for(i=0; i<instruction_length; ++i)
        get_stream_byte(in);

    //if(instruction_length)
        //printf("\n");

    flags = new_array(Byte, number_of_points);

    for(i=0; i<number_of_points; ++i)
    {
        //printf("flag %d\n", in->head);

        Byte flag = in->head;

        if(flag & REPEAT_FLAG)
        {
            get_stream_byte(in);
            int flag_count = in->head;

            if(i + flag_count >= number_of_points)
            {
                printf("error data\n");
                return 0;
            }

            for(j=0; j<flag_count && i<number_of_points; ++j, ++i)
                flags[i] = flag;
        }

        flags[i] = flag;
        get_stream_byte(in);
    }

    //*****************init bezier curves for contour***********************//

    for(i=0; i<number_of_contours; ++i)
        glyph->contours[i].number_of_curves = 0;

    int current_contour = 0;
    Byte point_not_on_a_curve = 0;

    for(i=0; i<number_of_points; ++i)
    {
        Byte flag = flags[i];

        if(flag & 1)
        {
            point_not_on_a_curve = 0;
        }
        else
        {
            if(!point_not_on_a_curve)
                --glyph->contours[current_contour].number_of_curves;

            point_not_on_a_curve = 1;
        }

        ++glyph->contours[current_contour].number_of_curves;


        if(i == last_point_numbers[current_contour])
        {
            //printf("%d curves in %d contour\n", glyph->contours[current_contour].number_of_curves, current_contour);
            ++current_contour;
        }
    }

    for(i=0; i<number_of_contours; ++i)
        glyph->contours[i].curves = new_array(BezierCurve*, glyph->contours[i].number_of_curves);

    //**********************************************************************//

    coords = new_array(short, 2*number_of_points);

    int contours_count = 0;

    for(i=0; i<number_of_points; ++i)
    {
        if(flags[i] & SHORT_X)
        {
            if(flags[i] & X_IS_POSITIVE)
            {
                previouse_x = in->head;
                previouse_real_x += previouse_x;
                coords[i*2] = previouse_real_x;
            }
            else
            {
                previouse_x = -in->head;
                previouse_real_x += previouse_x;
                coords[i*2] = previouse_real_x;
            }

            get_stream_byte(in);
        }
        else if(flags[i] & X_IS_SAME)
            coords[i*2] = previouse_real_x;
        else
        {
            previouse_x = get_bin_stream_short(in);
            previouse_real_x += previouse_x;
            coords[i*2] = previouse_real_x;
        }
    }

    for(i=0; i<number_of_points; ++i)
    {
        if(flags[i] & SHORT_Y)
        {
            if(flags[i] & Y_IS_POSITIVE)
            {
                previouse_y = in->head;
                previouse_real_y += previouse_y;
                coords[i*2+1] = previouse_real_y;
            }
            else
            {
                previouse_y = -in->head;
                previouse_real_y += previouse_y;
                coords[i*2+1] = previouse_real_y;
            }

            get_stream_byte(in);
        }
        else if(flags[i] & Y_IS_SAME)
        {
            coords[i*2+1] = previouse_real_y;
        }
        else
        {
            previouse_y = get_bin_stream_short(in);
            previouse_real_y += previouse_y;
            coords[i*2+1] = previouse_real_y;
        }
    }

    glyph->coords = coords;
    glyph->length = number_of_points;
    glyph->width  = x_max - x_min;
    glyph->height = y_max - y_min;

    Point2D *points;

    current_contour   = 0;
    int current_curve = 0;
    int points_count  = 0;
/*
    for(i=0; i<number_of_points; ++i)
    {
        printf("(%d, %d)\n", coords[i*2], coords[i*2+1]);
    }*/

    BezierCurve *last_curve;
    float aspect = (float)glyph->width / (float)glyph->height;

    point_not_on_a_curve = 0;

    for(i=0; i<number_of_points; ++i)
    {
        Byte flag = flags[i];

        if(i >= last_point_numbers[current_contour])
        {
            if(flags[i] & 1)
            {
                Point2D *points = create_points(2);

                points[0].x = coords[2*(i)] / 900.0f;//(float)glyph->width * aspect;
                points[0].y = coords[2*(i)+1] / 900.0f;//(float)glyph->height;

                points[1].x = glyph->contours[ current_contour ].curves[ 0 ]->points[0].x;
                points[1].y = glyph->contours[ current_contour ].curves[ 0 ]->points[0].y;

                glyph->contours[ current_contour ].curves[ current_curve ] = create_Bezier_curve(points, 2);

                //printf("%d curve, line (%f, %f) (%f, %f)\n", current_curve, points[0].x, points[0].y, points[1].x, points[1].y);
            }
            else
            {
                Point2D *points = create_points(3);

                if(flags[i-1] & 1)
                {
                    points[0].x = coords[2*(i-1)] / 900.0f;//(float)glyph->width * aspect;
                    points[0].y = coords[2*(i-1)+1] / 900.0f;//(float)glyph->height;
                }
                else
                {
                    points[0].x = glyph->contours[current_contour].curves[current_curve-1]->points[2].x;
                    points[0].y = glyph->contours[current_contour].curves[current_curve-1]->points[2].y;
                }

                points[1].x = coords[2*(i)] / 900.0f;//(float)glyph->width * aspect;
                points[1].y = coords[2*(i)+1] / 900.0f;//(float)glyph->height;

                points[2].x = glyph->contours[ current_contour ].curves[ 0 ]->points[0].x;
                points[2].y = glyph->contours[ current_contour ].curves[ 0 ]->points[0].y;

                glyph->contours[ current_contour ].curves[ current_curve ] = create_Bezier_curve(points, 3);

                //printf("%d curve, curve (%f, %f) (%f, %f) (%f, %f)\n", current_curve, points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y);
            }

            //printf("contour %d, total %d curves\n", current_contour, glyph->contours[ current_contour ].number_of_curves);

            ++current_contour;
            current_curve = 0;
            continue;
        }

        if(flags[i] & 1)
        {
            if(flags[i+1] & 1)
            {
                Point2D *points = create_points(2);

                points[0].x = (float)coords[2*i] / 900.0f;//(float)glyph->width * aspect;
                points[0].y = (float)coords[2*i+1] / 900.0f;//(float)glyph->width * aspect;

                points[1].x = (float)coords[2*(i+1)] / 900.0f;//(float)glyph->width * aspect;
                points[1].y = (float)coords[2*(i+1)+1] / 900.0f;//(float)glyph->width * aspect;

                glyph->contours[ current_contour ].curves[ current_curve ] = create_Bezier_curve(points, 2);

                //printf("line (%f, %f) (%f, %f)\n", points[0].x, points[0].y, points[1].x, points[1].y);

                ++current_curve;
            }
        }
        else
        {
            Point2D *points = create_points(3);

            points[1].x = coords[2*i] / 900.0f;//(float)glyph->width * aspect;
            points[1].y = coords[2*i+1] / 900.0f;//(float)glyph->width * aspect;

            if(flags[i-1] & 1)
            {
                points[0].x = coords[2*(i-1)] / 900.0f;//(float)glyph->width * aspect;
                points[0].y = coords[2*(i-1)+1] / 900.0f;//(float)glyph->height;
            }
            else
            {
                points[0].x = (coords[2*(i-1)] / 900.0f + points[1].x)/2.0f;//(float)glyph->width * aspect + points[1].x) / 2.0f;
                points[0].y = (coords[2*(i-1)+1] / 900.0f + points[1].y)/2.0f;//(float)glyph->height + points[1].y) / 2.0f;
            }

            if(flags[i+1] & 1)
            {
                points[2].x = coords[2*(i+1)] / 900.0f;//(float)glyph->width * aspect;
                points[2].y = coords[2*(i+1)+1] / 900.0f;//(float)glyph->height;
            }
            else
            {
                points[2].x = (coords[2*(i+1)] / 900.0f + points[1].x)/2.0f;//(float)glyph->width * aspect + points[1].x) / 2.0f;
                points[2].y = (coords[2*(i+1)+1] / 900.0f + points[1].y)/2.0f;//(float)glyph->height + points[1].y) / 2.0f;
            }

            glyph->contours[ current_contour ].curves[ current_curve ] = create_Bezier_curve(points, 3);

            //printf("curve (%f, %f) (%f, %f) (%f, %f)\n", points[0].x, points[0].y, points[1].x, points[1].y, points[2].x, points[2].y);

            ++current_curve;
        }
    }

    return glyph;
}


TTF* load_TTF(Stream *in)
{
    int            i;

    unsigned short number_of_tables;
    unsigned short search_range;
    unsigned short entry_selector;
    unsigned short range_shift;

    Byte           tag_name[5];
    unsigned int   checksum;
    unsigned int   offset;
    unsigned int   length;

    unsigned int   glyph_begin;
    unsigned int   glyph_length;

    TTF *ttf = new(TTF);

    tag_name[4] = '\0';

    if(!read_bytes_if_on_stream_head(in, "\x00\x01\x00\x00", 4))
    {
        printf("not TTF\n");
        goto error;
    }

    printf("TTF\n\n*********** Table Directory ***********\n\n");

    number_of_tables = get_bin_stream_ushort(in);
    printf("%d tables\n", number_of_tables);

    search_range = get_bin_stream_ushort(in);
    printf("search range is %d\n", search_range);

    entry_selector = get_bin_stream_ushort(in);
    printf("entry selector is %d\n", entry_selector);

    range_shift = get_bin_stream_ushort(in);
    printf("range shift is %d\n", range_shift);

    printf("\n**************** Tags *****************\n\n");
printf("offset %d\n", in->read_count);
    for(i=0; i<number_of_tables; ++i)
    {
        get_stream_bytes(in, tag_name, 4);
        printf("\n%s\n", tag_name);

        checksum = get_bin_stream_uint(in);
        printf("checksum is %d\n", checksum);

        offset = get_bin_stream_uint(in);
        printf("offset is %d\n", offset);

        length = get_bin_stream_uint(in);
        printf("length is %d\n", length);

        if( !strcmp(tag_name, "glyf") )
        {
            glyph_begin = offset;
        }
    }

    while(in->read_count != glyph_begin)
        get_stream_byte(in);

    ttf->glyphs = new_array(Glyph, 100);

    get_stream_byte(in);

    for(i=0; i<95; ++i)
        ttf->glyphs[i] = read_glyph(in);

    return ttf;

error:
    printf("error in load_TTF\n");

    return 0;
}


void convert_TTF_to_vector_font(TTF *ttf, Stream *output_stream)
{
    Byte *head = "Vector font";

    //write_data_in_output_stream()
}


Array* calculate_intersect_points(Glyph *glyph, float y)
{
    Array *intersect_points = create_array(2, 0);

    int i;
    int j;

    for(i=0; i < glyph->number_of_contours; ++i)
    {
        for(j=0; j<glyph->contours[i].number_of_curves; ++j)
        {
            BezierCurve *curve = glyph->contours[i].curves[j];

            float A = curve->points[0].y - curve->points[1].y;
            float B = curve->points[0].y - 2*curve->points[1].y + curve->points[2].y;

            if(B == 0 || curve->length == 2)
            {
                float t = (y - curve->points[0].y) / (curve->points[1].y - curve->points[0].y);

                if(t < 0 || t > 1)
                    continue;

                float x = (1 - t)*curve->points[0].x + t*curve->points[1].x;
                Point2D *intersect_point = create_points(1);
                intersect_point->x = x / 3.0f + 0.2f;
                intersect_point->y = y / 3.0f + 0.2f;

                push_in_array(intersect_points, intersect_point);

                continue;
            }

            float C = curve->points[0].y - y;
            float D = A*A - B*C;

            if(D < 0)
                continue;

            D = sqrt(D);

            float t1 = (A - D) / B;
            float t2 = (A + D) / B;

            if(t1 >= 0 && t1 <= 1)
            {
                float x = (1 - t1) * (1 - t1) * curve->points[0].x + 2 * t1 * (1 - t1) * curve->points[1].x + t1 * t1 * curve->points[2].x;
                Point2D *intersect_point = create_points(1);
                intersect_point->x = x / 3.0f + 0.2f;
                intersect_point->y = y / 3.0f + 0.2f;

                push_in_array(intersect_points, intersect_point);

                //printf("(%f, %f)\n", intersect_point->x, intersect_point->y);
            }

            if(t2 >= 0 && t2 <= 1)
            {
                float x = (1 - t2) * (1 - t2) * curve->points[0].x + 2 * t2 * (1 - t2) * curve->points[1].x + t2 * t2 * curve->points[2].x;
                //printf("%f\n", x);
                Point2D *intersect_point = create_points(1);
                intersect_point->x = x / 3.0f + 0.2f;
                intersect_point->y = y / 3.0f + 0.2f;

                push_in_array(intersect_points, intersect_point);

                //printf("(%f, %f)\n", intersect_point->x, intersect_point->y);
            }
        }
    }

    return intersect_points;
}


void sort_intersect_points(Array *points)
{
    int i;
    int j;

    for(i=0; i<points->length; ++i)
    {
        for(j=i; j<points->length; ++j)
        {
            Point2D *p1 = points->data[i];
            Point2D *p2 = points->data[j];

            if(p1->x > p2->x)
            {
                Point2D *tmp = p1;
                points->data[i] = points->data[j];
                points->data[j] = tmp;
            }
        }
    }
}


void fill_with_lines_canvas(Array *intersect_points, float y, Canvas *canvas)
{
    int i;
    int x;

    for(i=0; i+1<intersect_points->length; i+=2)
    {
        Point2D *p1 = intersect_points->data[i];
        Point2D *p2 = intersect_points->data[i+1];

        //printf("from (%f, %f) to (%f, %f)\n", p1->x, p1->y, p2->x, p2->y);

        rasterize_line(p1->x , p1->y, p2->x, p2->y, canvas);
    }
}


void rasterize_glyph(Glyph *glyph, Canvas *canvas)
{
    float y;

    Array *intersect_points;

    for(y=0; y<=1; y += 1.0f / (float)canvas->height)
    {
        intersect_points = calculate_intersect_points(glyph, y);
        sort_intersect_points(intersect_points);
        fill_with_lines_canvas(intersect_points, y, canvas);
    }
}