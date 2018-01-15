mkdir "%path%\include\system\devices\network\info\Windows"

copy "..\src\network info.h" "%path%\include\system\devices\network\info\network info.h"
copy "..\src\network info.c" "%path%\include\system\devices\network\info\network info.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\devices\network\info\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\devices\network\info\Windows\Windows.c"

exit