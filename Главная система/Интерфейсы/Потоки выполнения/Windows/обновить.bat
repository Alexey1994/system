mkdir "%path%\include\system\interfaces\thread\Windows"

copy "..\src\thread.h" "%path%\include\system\interfaces\thread\thread.h"
copy "..\src\thread.c" "%path%\include\system\interfaces\thread\thread.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\interfaces\thread\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\interfaces\thread\Windows\Windows.c"

exit