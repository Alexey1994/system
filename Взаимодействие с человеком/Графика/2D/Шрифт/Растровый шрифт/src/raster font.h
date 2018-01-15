#ifndef RASTER_FONT_H_INCLUDED
#define RASTER_FONT_H_INCLUDED


#include <data structures/character/character.h>
#include <human interface/graphics/canvas/canvas.h>
#include <input/input.h>
#include <output/output.h>


typedef struct
{
    Canvas glyphs[256];
}
Raster_Font;


function  Boolean      read_raster_font          (Raster_Font *font, Input *input);
procedure              write_raster_font         (Raster_Font *font, Output *output);
procedure              deinitialize_raster_font  (Raster_Font *font);

procedure              change_raster_glyph_color (Canvas *glyph, Byte red, Byte green, Byte blue);

function  N_32         text_width                (Character *text, Raster_Font *font);
function  N_32         text_height               (Character *text, Raster_Font *font);

function  N_32         character_width           (Character character, Raster_Font *font);
function  N_32         character_height          (Character character, Raster_Font *font);
//procedure              print_character           (Character c, N_32 x, N_32 y, Raster_Font *font);
procedure              print                     (Canvas *canvas, Character *text, N_32 x, N_32 y, Raster_Font *font);


#include "raster font.c"

#endif // RASTER_FONT_H_INCLUDED
