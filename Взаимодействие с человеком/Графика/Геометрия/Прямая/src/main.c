#include <libs/extends/extends.h>
#include "line.h"
#include <libs/graphics/graphics.h>


procedure draw(Canvas *canvas)
{
    Line          line;
	Point         begin;
	Point         end;
	static Canvas canvas;

	static is_initialize = 0;

	if(!is_initialize)
    {
        initialize_canvas(&canvas, 256, 256, 1);
        clear_canvas(&canvas);

        initialize_point(&begin, 2);
        initialize_point(&end, 2);

        begin.coords[0] = 0.5;
        begin.coords[1] = 0.5;

        end.coords[0] = 0;
        end.coords[1] = 0.5;

        initialize_line(&line, &begin, &end);
        rasterize_line(&line, &canvas);

        //rasterize_point(&begin, &canvas);

        is_initialize = 1;
    }
}


function N_32 main()
{
	initialize_graphics(1440, 900, 60, draw);

	for(;;);

    return 0;
}
