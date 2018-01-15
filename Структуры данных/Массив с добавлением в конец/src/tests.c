#include <stdio.h>
#include "array.h"


int main()
{
    Array array;
    Random_Access_Structure *structure;

    initialize_array(&array, 2, 0);
    structure = create_array_structure(&array);

    add_in_array(&array, 89);

    printf("%d", structure->get_element(structure, 0));
    deinitialize_array(&array);

    return 0;
}
