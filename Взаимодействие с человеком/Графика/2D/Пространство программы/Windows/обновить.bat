mkdir "%path%\include\libs\human interface"
mkdir "%path%\include\libs\human interface\graphics"
mkdir "%path%\include\libs\human interface\graphics\2D"
mkdir "%path%\include\libs\human interface\graphics\2D\program space"

copy "..\src\program space.h" "%path%\include\libs\human interface\graphics\2D\program space\program space.h"
copy "..\src\program space.c" "%path%\include\libs\human interface\graphics\2D\program space\program space.c"

exit