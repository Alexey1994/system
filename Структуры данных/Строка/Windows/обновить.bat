@mkdir "%path%\include\data structures"
@mkdir "%path%\include\data structures\string"

@copy "..\src\string.h" "%path%\include\data structures\string\string.h"
@copy "..\src\string.c" "%path%\include\data structures\string\string.c"

@exit