mkdir "%path%\include\system\interfaces\files\Windows"

copy "..\src\files.h" "%path%\include\system\interfaces\files\files.h"
copy "..\src\files.c" "%path%\include\system\interfaces\files\files.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\interfaces\files\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\interfaces\files\Windows\Windows.c"

exit