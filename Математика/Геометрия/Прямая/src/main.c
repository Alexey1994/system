#include <windows.h>
#define create_3D_point()
#include <extends/extends.h>
#include "line.h"
#include <system/devices/graphics/graphics.h>


procedure draw(Canvas *canvas)
{
	static is_initialize = 0;

	if(!is_initialize)
    {
        Line     line;
        Point_2D begin;
        Point_2D end;

        clear_canvas(canvas);

        initialize_point_2D(&begin, 100, 100);
        initialize_point_2D(&end, 200, 200);

        initialize_line(&line, &begin, &end);
        draw_line(&line, canvas);

        is_initialize = 1;
    }
}


function N_32 main()
{
	initialize_graphics(1440, 900, 60, draw);

	for(;;);

    return 0;
}
