function Byte* open_system_function (Byte *library_name, Byte *function_name)
{
    library_name = LoadLibraryA(library_name);

    if(!library_name)
        return 0;

    return GetProcAddress(library_name, function_name);
}

//tcc
#define add_function_argument_32(argument) \
    __asm__(                               \
        "push %0"                          \
        :                                  \
        :"r"(argument)                     \
    );

/*
//gcc
#define add_function_argument_32(argument) \
    __asm__(                               \
        "sub   $4, %%esp\n"                \
        "movl  %0, (%%esp)"                \
        :                                  \
        :"r"(argument)                     \
    );
*/


function Byte* run_system_function (function Byte* (*f)(), Byte **args, Z_32 length)
{
    for(length--; length>=0; length--)
        add_function_argument_32(args[length]);

    return f();
}
