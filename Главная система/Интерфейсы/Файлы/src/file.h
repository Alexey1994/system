#ifndef FILE_H_INCLUDED
#define FILE_H_INCLUDED


#include <input/input.h>


function  Boolean initialize_file_input  (Input *file_input, Character *path);
function  Boolean initialize_file_output (Output *file_output, Character *path);


#include "file.c"

#endif // FILE_H_INCLUDED
