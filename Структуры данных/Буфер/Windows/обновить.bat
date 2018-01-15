@mkdir "%path%\include\data structures"
@mkdir "%path%\include\data structures\buffer"

@copy "..\src\buffer.h" "%path%\include\data structures\buffer\buffer.h"
@copy "..\src\buffer.c" "%path%\include\data structures\buffer\buffer.c"

@exit