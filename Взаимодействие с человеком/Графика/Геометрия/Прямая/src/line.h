#ifndef LINE_H_INCLUDED
#define LINE_H_INCLUDED


#include <libs/human interface/graphics/canvas/canvas.h>
#include <libs/graphics/geometry/point/point.h>


typedef struct
{
	Point begin;
	Point end;
}
Line;


procedure       initialize_line   (Line *line, Point *begin, Point *end);
procedure       deinitialize_line (Line *line);
function  Line* create_line       (Point *begin, Point *end);
procedure       destroy_line      (Line *line);

procedure       rasterize_line    (Line *line, Canvas *canvas);


#include "line.c"

#endif // LINE_H_INCLUDED
