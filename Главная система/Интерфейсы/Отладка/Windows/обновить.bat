mkdir "%path%\include\system\interfaces\memory\Windows"

copy "..\src\memory.h" "%path%\include\system\interfaces\memory\memory.h"
copy "..\src\memory.c" "%path%\include\system\interfaces\memory\memory.c"
copy "..\src\Windows\Windows.h" "%path%\include\system\interfaces\memory\Windows\Windows.h"
copy "..\src\Windows\Windows.c" "%path%\include\system\interfaces\memory\Windows\Windows.c"

mkdir "%path%\include\system\interfaces\memory\x86 32 bit"

copy "..\src\x86 32 bit\x86 32 bit.h" "%path%\include\system\interfaces\memory\x86 32 bit\x86 32 bit.h"
copy "..\src\x86 32 bit\x86 32 bit.c" "%path%\include\system\interfaces\memory\x86 32 bit\x86 32 bit.c"

exit