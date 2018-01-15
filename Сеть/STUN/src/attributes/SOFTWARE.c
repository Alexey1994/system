#include "SOFTWARE.h"


void print_SOFTWARE_attribute(Byte *attribute, int length)
{
    int i;

    printf("\tSOFTWARE\n\t");

    for(i=0; i<length; ++i)
        printf("%c", attribute[i]);

    printf("\n");
}


void read_SOFTWARE_attribute(STUN_Attributes *attributes, Byte *attribute, int length)
{

}
