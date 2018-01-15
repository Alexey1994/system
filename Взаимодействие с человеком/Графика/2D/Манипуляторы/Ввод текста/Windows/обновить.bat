mkdir "%path%\include\libs\graphics"
mkdir "%path%\include\libs\graphics\GUI"
mkdir "%path%\include\libs\graphics\GUI\components"
mkdir "%path%\include\libs\graphics\GUI\components\text input"

copy "..\src\text input.h" "%path%\include\libs\graphics\GUI\components\text input\text input.h"
copy "..\src\text input.c" "%path%\include\libs\graphics\GUI\components\text input\text input.c"

exit