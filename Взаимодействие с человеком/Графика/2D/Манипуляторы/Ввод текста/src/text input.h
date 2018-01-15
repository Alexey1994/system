#ifndef TEXT_INPUT_H_INCLUDED
#define TEXT_INPUT_H_INCLUDED


#include <libs/extends/extends.h>
#include <libs/graphics/GUI/fonts/raster/font.h>
#include <libs/data structures/doubly linked list/doubly linked list.h>
#include <libs/graphics/primitives/2D/2D primitives.h>
#include <libs/input/input.h>
#include <libs/graphics/GUI/events/events.h>


typedef struct
{/*
    float                 x;
    float                 y;
    float                 width;
    float                 height;*/
    Rectangle             border;

    float                 active_color[3];
    float                 unactive_color[3];

    Font                 *font;

    DoublyLinkedList     *text;
    DoublyLinkedListNode *cursor;
}
TextInput;


TextInput* create_text_input        (float x, float y, float width, float height, Font *font);

Character* get_text_from_text_input (TextInput *text_input);
void       set_text_in_text_input   (TextInput *text_input, Character *text);

void       refresh_text_input       (TextInput *text_input);
void       destroy_text_input       (TextInput *text_input);


#include "text input.c"

#endif // TEXT_INPUT_H_INCLUDED
