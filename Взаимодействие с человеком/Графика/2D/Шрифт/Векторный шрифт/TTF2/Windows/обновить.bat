mkdir "%path%\include\libs\graphics"
mkdir "%path%\include\libs\graphics\GUI"
mkdir "%path%\include\libs\graphics\GUI\fonts"
mkdir "%path%\include\libs\graphics\GUI\fonts\TTF"

copy "..\src\TTF.h" "%path%\include\libs\graphics\GUI\fonts\TTF\TTF.h"
copy "..\src\TTF.c" "%path%\include\libs\graphics\GUI\fonts\TTF\TTF.c"

exit