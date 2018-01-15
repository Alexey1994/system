@mkdir "%path%\include\libs\compressors"
@mkdir "%path%\include\libs\compressors\RLE"

@copy "..\src\RLE.h" "%path%\include\libs\compressors\RLE\RLE.h"
@copy "..\src\RLE.c" "%path%\include\libs\compressors\RLE\RLE.c"

@exit