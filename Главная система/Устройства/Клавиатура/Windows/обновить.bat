mkdir "%path%\include\system\devices\keyboard\Windows"

copy "..\src\keyboard.h" "%path%\include\system\devices\keyboard\keyboard.h"
copy "..\src\keyboard.c" "%path%\include\system\devices\keyboard\keyboard.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\devices\keyboard\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\devices\keyboard\Windows\Windows.c"

mkdir "%path%\include\system\devices\keyboard\x86 32 bit"

copy "..\src\x86 32 bit\x86 32 bit.h" "%path%\include\system\devices\keyboard\x86 32 bit\x86 32 bit.h"
copy "..\src\x86 32 bit\x86 32 bit.c" "%path%\include\system\devices\keyboard\x86 32 bit\x86 32 bit.c"

exit