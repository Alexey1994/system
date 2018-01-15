void initialize_vector_glyph (Vector_Glyph *glyph)
{
	glyph->curves = create_array(2, 0);
}


void deinitialize_vector_glyph (Vector_Glyph *glyph)
{
	destroy_array(glyph->curves);
}


Vector_Glyph* create_vector_glyph ()
{
	Vector_Glyph *glyph = new(Vector_Glyph);
	initialize_vector_glyph(glyph);
	return glyph;
}


void destroy_vector_glyph (Vector_Glyph *glyph)
{
	deinitialize_vector_glyph(glyph);
	free(glyph);
}


Array* calculate_intersect_points(Vector_Glyph *glyph, float y)
{
    Array *intersect_points = create_array(2, 0);

    int i;
    int j;

    for(i=0; i < glyph->curves->length; ++i)
    {
        //for(j=0; j<glyph->contours[i].number_of_curves; ++j)
        //{
            Curve *curve = glyph->curves->data[i];

            Point *p1 = curve->points->data[0];
            Point *p2 = curve->points->data[1];
            Point *p3;

            float A = p1->coords[1] - p2->coords[1];
            float B = 0;

            if(curve->points->length == 3)
            {
                p3 = curve->points->data[2];
                B = p1->coords[1] - 2*p2->coords[1] + p3->coords[1];
            }

            if(curve->points->length == 2 || B == 0)
            {
                float t = (y - p1->coords[1]) / (p2->coords[1] - p1->coords[1]);

                if(t < 0 || t > 1)
                    continue;

                float x = (1 - t)*p1->coords[0] + t*p2->coords[0];
                Point *intersect_point = new(Point_2D);//create_point(2);
                initialize_point_2D(intersect_point, x, y);
                //intersect_point->coords[0] = x;
                //intersect_point->coords[1] = y;

                add_in_array(intersect_points, intersect_point);

                continue;
            }

            float C = p1->coords[1] - y;//curve->points[0].y - y;
            float D = A*A - B*C;

            if(D < 0)
                continue;

            D = sqrt(D);

            float t1 = (A - D) / B;
            float t2 = (A + D) / B;

            if(t1 >= 0 && t1 <= 1)
            {
                float x = (1 - t1) * (1 - t1) * p1->coords[0] + 2 * t1 * (1 - t1) * p2->coords[0] + t1 * t1 * p3->coords[0];
                Point *intersect_point = new(Point_2D);//create_point(2);
                initialize_point_2D(intersect_point, x, y);
                //intersect_point->coords[0] = x;
                //intersect_point->coords[1] = y;

                add_in_array(intersect_points, intersect_point);
            }

            if(t2 >= 0 && t2 <= 1)
            {
                //float x = (1 - t2) * (1 - t2) * curve->points[0].x + 2 * t2 * (1 - t2) * curve->points[1].x + t2 * t2 * curve->points[2].x;
                float x = (1 - t2) * (1 - t2) * p1->coords[0] + 2 * t2 * (1 - t2) * p2->coords[0] + t2 * t2 * p3->coords[0];
                Point *intersect_point = new(Point_2D);//create_point(2);
                initialize_point_2D(intersect_point, x, y);
                //intersect_point->coords[0] = x;
                //intersect_point->coords[1] = y;

                add_in_array(intersect_points, intersect_point);

                //printf("(%f, %f)\n", intersect_point->x, intersect_point->y);
            }
        //}
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
            Point *p1 = points->data[i];
            Point *p2 = points->data[j];

            if(p1->coords[0] > p2->coords[0])
            {
                Point *tmp = p1;
                points->data[i] = points->data[j];
                points->data[j] = tmp;
            }
        }
    }
}


void normalize_points(Array *points, Vector_Glyph *glyph)
{
    int i;

    for(i=0; i<points->length; ++i)
    {
        Point *point = array_data(points, i);

        //point->coords[0] += glyph->min_x;
        //point->coords[1] += glyph->min_y;

        point->coords[0] /= (float)glyph->max_x;
        point->coords[1] /= (float)glyph->max_y;
    }
}

//#include <GL/gl.h>

void fill_with_lines_canvas(Array *intersect_points, float y, Canvas *canvas)
{
    int i;
    int x;
/*
    glBegin(GL_LINES);

    for(i=0; i+1<intersect_points->length; i+=2)
    {
        Point *p1 = intersect_points->data[i];
        Point *p2 = intersect_points->data[i+1];
        Line   line;

        initialize_line(&line, p1, p2);

        printf("from (%f, %f) to (%f, %f)\n", p1->coords[0], p1->coords[1], p2->coords[0], p2->coords[1]);

        glColor3f(0,0,0);
        glVertex2f(p1->coords[0], p1->coords[1]);
        glVertex2f(p2->coords[0], p2->coords[1]);

        rasterize_line(&line, canvas);
        deinitialize_line(&line);
    }

    glEnd();*/
}


void rasterize_vector_glyph (Vector_Glyph *glyph, Canvas *canvas)
{
	float y;

    Array *intersect_points;

    //for(y=0; y<=1; y += 1.0f / (float)canvas->height)
    for(y=0; y<glyph->max_y; ++y)
    {
        intersect_points = calculate_intersect_points(glyph, y);
        sort_intersect_points(intersect_points);
        normalize_points(intersect_points, glyph);
        fill_with_lines_canvas(intersect_points, y, canvas);
    }
}
