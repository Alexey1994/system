typedef struct
{
    Z_32 x;
    Z_32 y;
}
Windows_Point;


private import function N_32 GetAsyncKeyState (N_32 key);
private import function N_32 GetCursorPos     (Windows_Point *coords);


#include "Windows.c"
