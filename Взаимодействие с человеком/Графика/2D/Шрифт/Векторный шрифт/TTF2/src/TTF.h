#ifndef TTF_H_INCLUDED
#define TTF_H_INCLUDED


#include <input/input.h>
#include <human interface/graphics/2D/fonts/vector font/vector font.h>


typedef struct
{
    Vector_Glyph **glyphs;
}
TTF;


Array* load_TTF(Input *input);


#include "TTF.c"

#endif // TTF_H_INCLUDED
