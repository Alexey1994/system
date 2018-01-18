mkdir "%path%\include\system\interfaces\debug\Windows"

copy "..\src\debug.h" "%path%\include\system\interfaces\debug\debug.h"
copy "..\src\debug.c" "%path%\include\system\interfaces\debug\debug.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\interfaces\debug\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\interfaces\debug\Windows\Windows.c"

mkdir "%path%\include\system\interfaces\debug\x86 32 bit"

copy "..\src\x86 32 bit\x86 32 bit.h" "%path%\include\system\interfaces\debug\x86 32 bit\x86 32 bit.h"
copy "..\src\x86 32 bit\x86 32 bit.c" "%path%\include\system\interfaces\debug\x86 32 bit\x86 32 bit.c"

exit