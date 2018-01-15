mkdir "%path%\include\system\devices\mouse\Windows"

copy "..\src\mouse.h" "%path%\include\system\devices\mouse\mouse.h"
copy "..\src\mouse.c" "%path%\include\system\devices\mouse\mouse.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\devices\mouse\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\devices\mouse\Windows\Windows.c"

exit