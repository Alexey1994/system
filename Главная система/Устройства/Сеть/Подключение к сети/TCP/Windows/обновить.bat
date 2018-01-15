mkdir "%path%\include\system\devices\network\connection\TCP\Windows"

copy "..\src\TCP.h" "%path%\include\system\devices\network\connection\TCP\TCP.h"
copy "..\src\TCP.c" "%path%\include\system\devices\network\connection\TCP\TCP.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\devices\network\connection\TCP\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\devices\network\connection\TCP\Windows\Windows.c"

exit