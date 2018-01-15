mkdir "%path%\include\libs\human interface"
mkdir "%path%\include\libs\human interface\graphics"
mkdir "%path%\include\libs\human interface\graphics\2D"
mkdir "%path%\include\libs\human interface\graphics\2D\manipulators"
mkdir "%path%\include\libs\human interface\graphics\2D\manipulators\button"

copy "..\src\button.h" "%path%\include\libs\human interface\graphics\2D\manipulators\button\button.h"
copy "..\src\button.c" "%path%\include\libs\human interface\graphics\2D\manipulators\button\button.c"

exit