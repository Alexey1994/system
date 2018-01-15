@mkdir "%path%\include\data structures"
@mkdir "%path%\include\data structures\queue"

@copy "..\src\queue.h" "%path%\include\data structures\queue\queue.h"
@copy "..\src\queue.c" "%path%\include\data structures\queue\queue.c"

@exit