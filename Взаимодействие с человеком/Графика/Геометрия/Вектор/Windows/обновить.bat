mkdir "%path%\include\libs\graphics"
mkdir "%path%\include\libs\graphics\geometry"
mkdir "%path%\include\libs\graphics\geometry\vector"

copy "..\src\vector.h" "%path%\include\libs\graphics\geometry\vector\vector.h"
copy "..\src\vector.c" "%path%\include\libs\graphics\geometry\vector\vector.c"