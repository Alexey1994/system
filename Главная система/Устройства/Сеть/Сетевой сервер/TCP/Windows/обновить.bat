mkdir "%path%\include\system\devices\network\server\TCP\Windows"

copy "..\src\TCP.h" "%path%\include\system\devices\network\server\TCP\TCP.h"
copy "..\src\TCP.c" "%path%\include\system\devices\network\server\TCP\TCP.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\devices\network\server\TCP\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\devices\network\server\TCP\Windows\Windows.c"

exit