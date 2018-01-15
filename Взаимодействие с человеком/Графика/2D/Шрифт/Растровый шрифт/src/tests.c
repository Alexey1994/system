#include <windows.h>
#include <system/devices/graphics/graphics.h>
#include "raster font.h"
#include <system/interfaces/files/files.h>


void draw(Canvas *canvas)
{
    static Boolean      once   =  1;
    static Raster_Font  font;
    Input               input;

    if(once)
    {
        initialize_file_input(&input, "default.fnt");

        if(!read_raster_font(&font, &input))
            printf("font not readed\n");

        deinitialize_input(&input);

        once=0;
    }

    print(canvas, "Alexey Borisenko", 0, 0, &font);
}


int main()
{
    initialize_graphics(1440, 900, 60, draw);

    for(;;){}

    return 0;
}
