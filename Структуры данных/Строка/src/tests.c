#include <stdio.h>
#include "string.h"


function int main()
{
    String string;
    String string2;

    initialize_string(&string);

    write_byte(&string.output, 'H');
    write_N_32(&string.output, 1234);
    print_string(&string);

    initialize_string(&string2);
    write_byte(&string2.output, 'H');

    printf("\ncompare %d\n", compare_strings(&string, &string2));

    return 0;
}
