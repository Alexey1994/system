mkdir "%path%\include\libs\human interface"
mkdir "%path%\include\libs\human interface\graphics"
mkdir "%path%\include\libs\human interface\graphics\animation"

copy "..\src\animation.c" "%path%\include\libs\human interface\graphics\animation\animation.c"
copy "..\src\animation.h" "%path%\include\libs\human interface\graphics\animation\animation.h"

exit