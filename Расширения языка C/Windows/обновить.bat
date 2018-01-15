@mkdir "%path%\include\extends\x86 32 bit"

@copy "..\src\extends.h" "%path%\include\extends\extends.h"
@copy "..\src\extends.c" "%path%\include\extends\extends.c"
@copy "..\src\x86 32 bit\x86 32 bit.h" "%path%\include\extends\x86 32 bit\x86 32 bit.h"
@copy "..\src\x86 32 bit\x86 32 bit.c" "%path%\include\extends\x86 32 bit\x86 32 bit.c"

@exit