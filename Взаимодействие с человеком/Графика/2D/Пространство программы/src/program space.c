function Program_Space_Element* create_program_space_element (
    Byte       *element,
    procedure (*refresh_element)(Byte *element),
    procedure (*destroy_element)(Byte *element)
)
{
    Program_Space_Element *program_space_element;

    program_space_element = new(Program_Space_Element);

    program_space_element->element          =  element;
    program_space_element->refresh_element  =  refresh_element;
    program_space_element->destroy_element  =  destroy_element;

    return program_space_element;
}


procedure destroy_program_space_element(Program_Space_Element *program_space_element)
{
    program_space_element->destroy_element(program_space_element->element);
    free(program_space_element);
}


function Program_Space* create_program_space (N_32 x, N_32 y, N_32 width, N_32 height)
{
    Program_Space *program_space;

    program_space = new(Program_Space);

    program_space->x        = x;
    program_space->y        = y;
    program_space->width    = width;
    program_space->height   = height;
    program_space->elements = create_array(0, destroy_program_space_element);

    return program_space;
}


procedure destroy_program_space (Program_Space *program_space)
{
    destroy_array(program_space->elements);
    free(program_space);
}


procedure add_element_in_program_space (Program_Space *program_space, Program_Space_Element *program_space_element)
{
    add_in_array(program_space->elements, program_space_element);
}


procedure refresh_program_space (Program_Space *program_space)
{
    N_32                   i;
    Program_Space_Element *program_space_element;

    for(i=0; i<program_space->elements->length; ++i)
    {
        program_space_element = program_space->elements->data[i];
        program_space_element->refresh_element(program_space_element->element);
    }
}