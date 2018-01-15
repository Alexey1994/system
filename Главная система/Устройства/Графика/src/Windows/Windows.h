#define UNIQUE_FOR_EACH_WINDOW_CONTEXT_CLASS_STYLE  32

#define CLOSE_WINDOW_MESSAGE                        16
#define DESTROY_WINDOW_MESSAGE                      2
#define PAINT_WINDOW_MESSAGE                        15
#define ERASE_BACKGROUND_MESSAGE                    20

#define DEFAULT_ICON                                32512
#define DEFAULT_ARROW                               32512

#define POPUP_WINDOW_STYLE                          0x80000000
#define SHOW_MAXIMIZED_WINDOW                       3

#define REMOVED_FROM_QUEUE_MESSAGE                  1
#define QUIT_WINDOW_MESSAGE                         0x0012
#define UPDATE_NOW                                  256


typedef struct
{

}
Icon;

typedef struct
{

}
Cursor;

typedef struct
{

}
Brush;

typedef struct
{
    N_32            structure_size;
    N_32            style;
    function N_32 (*window_procedure)();
    N_32            class;
    Byte           *window;
    N_16           *instance;
    Icon           *icon;
    Cursor         *cursor;
    Brush          *background;
    Byte           *menu_name;
    Byte           *class_name;
    Icon           *small_icon;
}
Window_Class;

typedef struct
{
    N_32 size_of_structure;
    Z_32 width;
    Z_32 height;
    N_16 planes;
    N_16 bit_count;
    N_32 compression;
    N_32 size_image;
    Z_32 x_pels_per_meter;
    Z_32 y_pels_per_meter;
    N_32 number_of_color_indexes;
    N_32 number_of_color_indexes_important;
}
Bitmap_Info_Header;

typedef struct
{
    Bitmap_Info_Header header;
    N_32               color[1];
}
Bitmap_Info;

typedef struct
{
    Z_32 left;
    Z_32 top;
    Z_32 right;
    Z_32 botom;
}
Windows_Rectangle;

typedef struct
{
    Byte              *context;
    Z_32               erase_background;
    Windows_Rectangle  rectangle;
    Z_32               restore;
    Z_32               update;
    Byte               color[32];
}
Windows_Paint;

typedef struct
{
    Z_32 x;
    Z_32 y;
}
Windows_Point;

typedef struct
{
    Byte          *window;
    N_32           message;
    N_32          *parameters1;
    Z_32          *parameters2;
    N_32           time;
    Windows_Point  point;
}
Windows_Message;


private import stdcall procedure          PostQuitMessage  (N_32 exit_code);
private import stdcall function  Byte*    BeginPaint       (Byte *window, Windows_Paint *paint);
private import stdcall function  N_32     EndPaint         (Byte *window, Windows_Paint *paint);
private import stdcall function  N_32     DefWindowProcA    (Byte *window, N_32 message, N_16 *parameter1, N_32 *parameter2);
private import stdcall function  Icon*    LoadIconA        (Byte *instance, Byte *icon_name);
private import stdcall function  Cursor*  LoadCursorA      (Byte *instance, Byte *cursor_name);
private import stdcall function  N_16     RegisterClassExA (Window_Class *class);
private import stdcall function  N_32     ShowWindow       (Byte *window, N_32 options);
private import stdcall function  Byte*    GetDC            (Byte *window);
private import stdcall function  N_32     PeekMessageA     (Windows_Message *message, Byte *window, N_32 filter_min, N_32 filter_max, N_32 remove_message);
private import stdcall function  Z_32     DispatchMessageA (Windows_Message *message);
private import stdcall function  N_32     TranslateMessage (Windows_Message *message);
private import stdcall function  N_32     InvalidateRect   (Byte *window, Windows_Rectangle *rectangle, N_32 clean);
private import stdcall function  N_32     UpdateWindow     (Byte *window);
private import stdcall function  N_32     RedrawWindow     (Byte *window, Windows_Rectangle *region, Byte *update_region, N_32 flags);

private import stdcall function  Z_32     SetDIBitsToDevice(
    Byte        *device_context,
    Z_32         x,
    Z_32         y,
    N_32         width,
    N_32         height,
    Z_32         x_image,
    Z_32         y_image,
    N_32         start_scan,
    N_32         scan_lines_length,
    Byte        *image,
    Bitmap_Info *bitmap_info,
    N_32         color_type
);

private import stdcall function  Byte*   CreateWindowExA(
    N_32 extended_style,
    Byte *class_name,
    Byte *window_name,
    N_32 style,
    Z_32 x,
    Z_32 y,
    Z_32 width,
    Z_32 height,
    Byte *parent_window,
    Byte *menu,
    Byte *instance,
    N_32 *parameters
);


#include "Windows.c"
