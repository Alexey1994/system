mkdir "%path%\include\libs\human interface"
mkdir "%path%\include\libs\human interface\audio"
mkdir "%path%\include\libs\human interface\audio\WAV"

copy "..\src\WAV.h" "%path%\include\libs\audio\WAV\WAV.h"
copy "bin\Debug\libmain.a" "%path%\include\libs\audio\WAV\WAV.a"

exit