#include <extends/extends.h>
#include "TTF.h"

//#include <libs/mathematic/geometry/line/line.h>
//#include <graphics/graphics.h>
#include <system/interfaces/files/files.h>


procedure rasterize_glyph_to_SVG(Vector_Glyph *glyph, N_32 index)
{
    N_32   i;
    N_32   j;
    Curve *curve;
    Point *point;

    Byte buf[10] = {0};
    snprintf(buf, 10, "%d.html", index);

    Byte *SVG_file = fopen(buf, "wb");

    fputs("<svg style=\"width:100%; height:100%\">", SVG_file);

    for(i=0; i<glyph->curves->length; ++i)
    {
        curve = array_data(glyph->curves, i);//glyph->curves->data[i];

        /*for(j=0; j<curve->points->length; ++j)
        {
            Point *point = array_data(curve->points, j);

            printf("(%f, %f)", point->coords[0], point->coords[1]);
        }*/

        if(curve->points->length == 2)
        {
            fputs("<path d=\"", SVG_file);

            point = array_data(curve->points, 0);
            fprintf(SVG_file, "M%f,%f", point->coords[0] / 10.0f + 30.0f, (glyph->max_y - point->coords[1]) / 10.0f + 30.0f);

            point = array_data(curve->points, 1);
            fprintf(SVG_file, " %f,%f", point->coords[0] / 10.0f + 30.0f, (glyph->max_y - point->coords[1]) / 10.0f + 30.0f);

            fputs("\" stroke=\"#000\" />\n", SVG_file);
        }

        if(curve->points->length == 3)
        {
            fputs("<path d=\"", SVG_file);

            point = array_data(curve->points, 0);
            fprintf(SVG_file, "M%f,%f", point->coords[0] / 10.0f + 30.0f, (glyph->max_y - point->coords[1]) / 10.0f + 30.0f);

            point = array_data(curve->points, 1);
            fprintf(SVG_file, " Q%f,%f", point->coords[0] / 10.0f + 30.0f, (glyph->max_y - point->coords[1]) / 10.0f + 30.0f);

            point = array_data(curve->points, 2);
            fprintf(SVG_file, " %f,%f", point->coords[0] / 10.0f + 30.0f, (glyph->max_y - point->coords[1]) / 10.0f + 30.0f);

            fputs("\" stroke=\"#000\" fill=\"none\" />\n", SVG_file);
        }

        //printf("\n");
    }

    fputs("</svg>", SVG_file);
    fclose(SVG_file);
}


function int main()
{
    Input  input;
    Array *glyphs;

    initialize_file_input(&input, "a.ttf");
    glyphs = load_TTF(&input);

    return 0;
}
