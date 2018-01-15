mkdir "%path%\include\system\interfaces\system library\Windows"

copy "..\src\system library.h" "%path%\include\system\interfaces\system library\system library.h"
copy "..\src\system library.c" "%path%\include\system\interfaces\system library\system library.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\interfaces\system library\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\interfaces\system library\Windows\Windows.c"

exit