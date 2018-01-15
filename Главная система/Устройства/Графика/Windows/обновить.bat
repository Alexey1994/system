mkdir "%path%\include\system\devices\graphics\Windows"

copy "..\src\graphics.h" "%path%\include\system\devices\graphics\graphics.h"
copy "..\src\graphics.c" "%path%\include\system\devices\graphics\graphics.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\devices\graphics\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\devices\graphics\Windows\Windows.c"

exit