#include <windows.h>
#include "files.h"


N_32 main()
{
    Input file_input;

    initialize_file_input(&file_input, "a.txt");
    printf("%c\n", read_byte(&file_input));
    deinitialize_input(&file_input);

    return 0;
}
