#include <windows.h>
#include "file.h"


N_32 main()
{
    Input file_input;

    initialize_file_input(&file_input, "a.txt");
    //if(!initialize_file_input(&file_input, "\\\\.\\ROOT\\NET\\0001"))
    //    printf("error");

    printf("%d", GetLastError());
    //printf("%c\n", read_byte(&file_input));
    //deinitialize_input(&file_input);

    return 0;
}
