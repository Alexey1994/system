mkdir "%path%\include\system\interfaces\file\Windows"

copy "..\src\file.h" "%path%\include\system\interfaces\file\file.h"
copy "..\src\file.c" "%path%\include\system\interfaces\file\file.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\interfaces\file\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\interfaces\file\Windows\Windows.c"

exit