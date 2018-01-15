mkdir "%path%\include\libs\human interface"
mkdir "%path%\include\libs\human interface\graphics"
mkdir "%path%\include\libs\human interface\graphics\2D"
mkdir "%path%\include\libs\human interface\graphics\2D\images"
mkdir "%path%\include\libs\human interface\graphics\2D\images\TGA"

copy "..\src\TGA.h" "%path%\include\libs\human interface\graphics\2D\images\TGA\TGA.h"
copy "..\src\TGA.c" "%path%\include\libs\human interface\graphics\2D\images\TGA\TGA.c"

exit