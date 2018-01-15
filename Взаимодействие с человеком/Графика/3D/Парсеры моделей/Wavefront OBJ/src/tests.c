#include <windows.h>
#include <system/interfaces/files/files.h>
#include "OBJ parser.h"


int main()
{
    Input       file_input;
    StaticModel model;

    initialize_file_input(&file_input, "test");
    parse_OBJ(&model, &file_input, &initialize_file_input);

    return 0;
}
