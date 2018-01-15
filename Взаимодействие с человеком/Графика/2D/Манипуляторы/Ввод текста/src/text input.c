#include <GL/gl.h>


static Byte *active_text_input = 0;


TextInput* create_text_input(float x, float y, float width, float height, Font *font)
{
    TextInput *text_input = new(TextInput);

    text_input->border.x      = x;
    text_input->border.y      = y;
    text_input->border.width  = width;
    text_input->border.height = height;

    text_input->font          = font;

    text_input->text          = create_doubly_linked_list(0);
    text_input->cursor        = 0;

    return text_input;
}


void destroy_text_input(TextInput *text_input)
{
    destroy_doubly_linked_list(text_input->text);
    free(text_input);
}


Character* get_text_from_text_input(TextInput *text_input)
{
    Character            *text      = malloc(text_input->text->length + 1);
    DoublyLinkedListNode *list_node = text_input->text->begin;
    int                   i;

    for(i=0; list_node && i<text_input->text->length; ++i, list_node = list_node->next)
        text[i] = list_node->data;

    text[i] = '\0';

    return text;
}


void set_text_in_text_input(TextInput *text_input, Character *text)
{
    destroy_doubly_linked_list(text_input->text);
    create_doubly_linked_list(0);

    for(; *text; ++text)
        add_in_doubly_linked_list(text_input->text, text_input->text->length, *text);
}


static void graphics_print_doubly_linked_list(DoublyLinkedList *text, float x, float y, Font *font)
{
    DoublyLinkedListNode *begin;
    Character             c;

    for(begin = text->begin; begin; begin = begin->next)
    {
        c = begin->data;

        print_character(c, x, y, font);
        x += get_character_width(c, font);
    }
}


static void draw_text_input(TextInput *text_input)
{
    glColor3fv(text_input->active_color);
    draw_rectangle(&text_input->border);

    glColor3f(0, 0, 0);
    graphics_print_doubly_linked_list(text_input->text, text_input->border.x, text_input->border.y, text_input->font);
}


static void add_character_after_text_input_cursor(TextInput *text_input, Character c)
{
    DoublyLinkedListNode *node;

    if(!text_input->cursor)
    {
        if(!text_input->text->begin)
        {
            text_input->cursor = create_doubly_linked_list_node(0, 0, c);
            text_input->text->begin  = text_input->cursor;
            text_input->text->length++;
            return;
        }

        text_input->cursor = text_input->text->begin;
    }

    node = create_doubly_linked_list_node(text_input->cursor, text_input->cursor->next, c);
    text_input->cursor = node;
    text_input->text->length++;
}


static void del_character_after_text_input_cursor(TextInput *text_input)
{
    DoublyLinkedListNode *del_node;

    if(!text_input->cursor)
        return;

    text_input->cursor = text_input->cursor->previouse;

    if(text_input->cursor)
        destroy_doubly_linked_list_node(text_input->cursor->next);
    else
    {
        del_node = text_input->text->begin;
        text_input->text->begin = text_input->text->begin->next;
        destroy_doubly_linked_list_node(del_node);
    }

    text_input->text->length--;
}


static void move_cursor_left(TextInput *text_input)
{
    if(text_input->cursor)
        text_input->cursor = text_input->cursor->previouse;
}


static void listen_characters(TextInput *text_input)
{
    Character key_code = get_pressed_key_code();

    if(key_code >= 'A' && key_code <= 'Z' ||
       key_code >= '0' && key_code <= '9' ||
       key_code == ' ')
        add_character_after_text_input_cursor(text_input, key_code);
    else if(key_code == VK_BACK)
        del_character_after_text_input_cursor(text_input);
    else if(key_code == VK_LEFT)
        move_cursor_left(text_input);
}


void refresh_text_input(TextInput *text_input)
{
    if(clicked(on_rectangle, &text_input->border))
        active_text_input = text_input;

    if(text_input == active_text_input)
        listen_characters(text_input);

    draw_text_input(text_input);
}
