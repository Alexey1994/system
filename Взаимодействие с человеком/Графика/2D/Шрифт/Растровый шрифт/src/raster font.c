function Boolean read_raster_font (Raster_Font *font, Input *input)
{
    R_32         glyph_coords[256][4];
    N_32         i;
    N_32         width;
    N_32         height;
    N_32         glyph_start_x;
    N_32         glyph_start_y;
    N_32         glyph_end_x;
    N_32         glyph_end_y;
    N_32         glyph_width;
    N_32         glyph_height;
    Canvas       glyphs;

    if(!read_if_next(input, "FONT"))
        return 0;

    for(i=0; i<256; ++i)
    {
        glyph_coords[i][0] = read_binary_R_32(input);
        glyph_coords[i][1] = read_binary_R_32(input);
        glyph_coords[i][2] = read_binary_R_32(input);
        glyph_coords[i][3] = read_binary_R_32(input);
    }

    width = read_binary_N_32(input);
    height = read_binary_N_32(input);

    initialize_canvas(&glyphs, width, height, 4);
    read_byte_array(input, glyphs.data, width*height*4);

    for(i=0; i<256; ++i)
    {
        glyph_start_x = width * glyph_coords[i][0];
        glyph_start_y = height * glyph_coords[i][1];
        glyph_end_x   = width * glyph_coords[i][2];
        glyph_end_y   = height * glyph_coords[i][3];

        glyph_width = glyph_end_x - glyph_start_x;
        glyph_height = glyph_end_y - glyph_start_y;

        initialize_canvas(&font->glyphs[i], glyph_width, glyph_height, 4);
        clear_canvas(&font->glyphs[i]);

        N_32 x;
        N_32 y;

        for(y=glyph_start_y; y<glyph_end_y; ++y)
        {
            for(x=glyph_start_x; x<glyph_end_x; ++x)
            {
                Byte *pixel     = get_canvas_pixel(&glyphs, x, y);
                Byte *pixel_out = get_canvas_pixel(&font->glyphs[i], x - glyph_start_x, y - glyph_start_y);

                pixel_out[0] = 0;
                pixel_out[1] = 0;
                pixel_out[2] = 0;
                pixel_out[3] = pixel[3];
            }
        }

        change_raster_glyph_color(&font->glyphs[i], 255, 255, 255);
    }

    deinitialize_canvas(&glyphs);

    return 1;
}


procedure write_raster_font (Raster_Font *font, Output *output)
{

}


procedure deinitialize_raster_font (Raster_Font *font)
{
    N_32 i;

    for(i=0; i<256; ++i)
        deinitialize_canvas(&font->glyphs[i]);
}


procedure change_raster_glyph_color (Canvas *glyph, Byte red, Byte green, Byte blue)
{
    N_32  x;
    N_32  y;
    Byte *current_pixel;

    for(y=0; y<glyph->height; ++y)
    {
        for(x=0; x<glyph->width; ++x)
        {
            current_pixel = get_canvas_pixel(glyph, x, y);

            current_pixel[0] = blue;//blue * current_pixel[3] / 255;
            current_pixel[1] = green;//green * current_pixel[3] / 255;
            current_pixel[2] = red;//red * current_pixel[3] / 255;
        }
    }
}


function N_32 text_width (Character *text, Raster_Font *font)
{
    N_32 width = 0;

    for(; *text; ++text)
        width += character_width(*text, font);

    return width;
}


function N_32 text_height (Character *text, Raster_Font *font)
{
    return character_height(*text, font);
}


function N_32 character_width (Character character, Raster_Font *font)
{
    return font->glyphs[character].width;
}


function N_32 character_height (Character character, Raster_Font *font)
{
    return font->glyphs[character].height;
}


procedure print (Canvas *canvas, Character *text, N_32 x, N_32 y, Raster_Font *font)
{
    for(; *text; ++text)
    {
        draw_canvas_on_canvas(canvas, &font->glyphs[*text], x, y);
        x += character_width(*text, font);
    }
}
