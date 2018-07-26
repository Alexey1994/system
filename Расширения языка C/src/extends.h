#ifndef EXTENDS_H_INCLUDED
#define EXTENDS_H_INCLUDED


#define loop       for(;;)
#define increment  ++
#define private    static
#define procedure  void
#define function


typedef char                   Z_8;
typedef short int              Z_16;
typedef long int               Z_32;
typedef long long int          Z_64;

typedef unsigned char          N_8;
typedef unsigned short int     N_16;
typedef unsigned long int      N_32;
typedef unsigned long long int N_64;

typedef float                  R_32;
typedef long                   R_64;

typedef unsigned char          Byte;
typedef unsigned char          Boolean;


typedef struct
{
    Byte *data;
    Byte  type;
}
Dynamic_Data;


#include <system/interfaces/memory/memory.h>


#define new(type)                             allocate_memory(sizeof(type))
#define new_array(type, length)               allocate_memory(sizeof(type)*length)

//#define reallocate(data, type)                data=reallocate_memory(data, sizeof(type))
//#define reallocate_array(data, type, length)  data=reallocate_memory(data, sizeof(type)*length)

procedure copy_memory             (Byte *data1, Byte *data2, N_32 length);

procedure initialize_dynamic_data (Dynamic_Data *dynamic_data, Byte *data, Byte type);
procedure revert_bytes_order      (Byte *array, N_32 length);
procedure swap                    (Byte *element1, Byte *element2, N_32 length);

#ifdef BIG_ENDIAN
    #define convert_little_to_big_endian(array, length)
    #define convert_big_to_little_endian                revert_bytes_order
#else
    #define convert_little_to_big_endian                revert_bytes_order
    #define convert_big_to_little_endian(array, length)
#endif


#include "extends.c"

#endif // EXTENDS_H_INCLUDED
