mkdir "%path%\include\system\devices\sound\Windows"
copy "..\src\sound.h" "%path%\include\system\devices\sound\sound.h"
copy "..\src\sound.c" "%path%\include\system\devices\sound\sound.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\devices\sound\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\devices\sound\Windows\Windows.c"

exit