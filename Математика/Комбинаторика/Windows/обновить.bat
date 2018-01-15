mkdir "%path%\include\mathematic"
mkdir "%path%\include\mathematic\combinatorics"

copy "..\src\combinatorics.h" "%path%\include\mathematic\combinatorics\combinatorics.h"
copy "..\src\combinatorics.c" "%path%\include\mathematic\combinatorics\combinatorics.c"

exit