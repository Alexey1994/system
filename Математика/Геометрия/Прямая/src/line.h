#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED


#include <human interface/graphics/canvas/canvas.h>
#include <mathematic/geometry/vector/vector.h>
#include <mathematic/geometry/point/point.h>


typedef struct
{
	Point *begin;
	Point *end;
}
Line;


procedure       initialize_line   (Line *line, Point *begin, Point *end);
//function  Line* create_line       (Point *begin, Point *end);
//procedure       destroy_line      (Line *line);

procedure       draw_line         (Line *line, Canvas *canvas);


#include "line.c"

#endif // LINE_H_INCLUDED
