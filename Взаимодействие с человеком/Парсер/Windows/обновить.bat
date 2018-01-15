mkdir "%path%\include\libs\parser"

copy "..\src\parser.h" "%path%\include\libs\parser\parser.h"
copy "..\src\parser.c" "%path%\include\libs\parser\parser.c"
copy "..\src\tokenizer.h" "%path%\include\libs\parser\tokenizer.h"
copy "..\src\tokenizer.c" "%path%\include\libs\parser\tokenizer.c"

exit