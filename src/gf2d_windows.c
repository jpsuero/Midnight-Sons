#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gf2d_windows.h"
#include "simple_logger.h"

typedef struct
{
    Sprite *generic_border;
    Sprite *generic_background;
    Window *window_list;    /**<*/
    int window_max;         /**<how many windows can exist at once*/
    List *window_deque;     /**<draw order is back to front, update order is front to back*/
}WindowManager;

static WindowManager window_manager = {0};

void gf2d_draw_window_border_generic(Rect rect,Vector4D color)
{
    gf2d_draw_window_border(window_manager.generic_border,window_manager.generic_background,rect,color);
}

void gf2d_draw_window_border(Sprite *border,Sprite *bg,Rect rect,Vector4D color)
{
    Vector2D scale = {0};
    if (bg)
    {
        scale.x = rect.w/bg->frame_w;
        scale.y = rect.h/bg->frame_h;
        gf2d_sprite_draw(
            bg,
            vector2d(rect.x,rect.y),
            &scale,
            NULL,
            NULL,
            NULL,
            &color,
            0);
    }
    if (!border)return;
    scale.x = (rect.w - border->frame_w)/(float)border->frame_w;
    scale.y = 1;
    gf2d_sprite_draw(
        border,
        vector2d(rect.x + border->frame_w/2,rect.y - border->frame_w/2),
        &scale,
        NULL,
        NULL,
        NULL,
        &color,
        BE_Top);
    gf2d_sprite_draw(
        border,
        vector2d(rect.x + border->frame_w/2,rect.y + rect.h- border->frame_w/2),
        &scale,
        NULL,
        NULL,
        NULL,
        &color,
        BE_Bottom);

    scale.y = (rect.h - border->frame_h)/(float)border->frame_h;
    scale.x = 1;

    gf2d_sprite_draw(
        border,
        vector2d(rect.x - border->frame_w/2,rect.y + border->frame_w/2),
        &scale,
        NULL,
        NULL,
        NULL,
        &color,
        BE_Left);
    gf2d_sprite_draw(
        border,
        vector2d(rect.x + rect.w - border->frame_w/2,rect.y + border->frame_w/2),
        &scale,
        NULL,
        NULL,
        NULL,
        &color,
        BE_Right);
    
    gf2d_sprite_draw(
        border,
        vector2d(rect.x + rect.w - border->frame_w/2,rect.y - border->frame_w/2),
        NULL,
        NULL,
        NULL,
        NULL,
        &color,
        BE_TR);
    gf2d_sprite_draw(
        border,
        vector2d(rect.x - border->frame_w/2,rect.y + rect.h - border->frame_w/2),
        NULL,
        NULL,
        NULL,
        NULL,
        &color,
        BE_BL);
    gf2d_sprite_draw(
        border,
        vector2d(rect.x - border->frame_w/2,rect.y - border->frame_w/2),
        NULL,
        NULL,
        NULL,
        NULL,
        &color,
        BE_TL);
    gf2d_sprite_draw(
        border,
        vector2d(rect.x + rect.w - border->frame_w/2,rect.y + rect.h - border->frame_w/2),
        NULL,
        NULL,
        NULL,
        NULL,
        &color,
        BE_BR);
}

void gf2d_windows_close()
{
    int i;
    for (i = 0;i < window_manager.window_max;i++)
    {
        if (window_manager.window_list[i]._inuse)
        {
            gf2d_window_free(&window_manager.window_list[i]);
        }
    }
    gf2d_list_delete(window_manager.window_deque);
    slog("window system closed");
}

void gf2d_windows_init(int max_windows)
{
    if (max_windows <= 0)
    {
        slog("cannot initilize window system for 0 windows");
        return;
    }
    window_manager.window_list = (Window*)malloc(sizeof(Window)*max_windows);
    if(window_manager.window_list == NULL)
    {
        slog("failed to allocate memory for window system");
        return;
    }
    memset(window_manager.window_list,0,sizeof(Window)*max_windows);
    window_manager.window_max = max_windows;
    window_manager.window_deque = gf2d_list_new();
    window_manager.generic_background = gf2d_sprite_load_image("images/window_background.png");
    window_manager.generic_border = gf2d_sprite_load_all("images/window_border.png",64,64,8);
    slog("window system initilized");
    atexit(gf2d_windows_close);
}

void gf2d_window_free(Window *win)
{
    int i,count;
    if (!win)return;
    if (win->free_data != NULL)
    {
        win->free_data(win);
    }
    gf2d_list_delete_data(window_manager.window_deque,win);
    count = gf2d_list_get_count(win->elements);
    for (i = 0;i < count;i++)
    {
        gf2d_element_free((Element*)gf2d_list_get_nth(win->elements,i));
    }
    gf2d_list_delete(win->elements);
    gf2d_sprite_free(win->background);
    gf2d_sprite_free(win->border);
    memset(win,0,sizeof(Window));
}

void gf2d_window_draw(Window *win)
{
    int count,i;
    Vector2D offset;
    if (!win)return;
    if (!win->no_draw_generic)
    {
        gf2d_draw_window_border_generic(win->dimensions,win->color);
    }
    offset.x = win->dimensions.x + win->canvas.x;
    offset.y = win->dimensions.y + win->canvas.y;
    count = gf2d_list_get_count(win->elements);
    for (i = 0;i < count;i++)
    {
        gf2d_element_draw((Element *)gf2d_list_get_nth(win->elements,i), offset);
    }
}

Window *gf2d_window_new()
{
    int i;
    for (i = 0;i < window_manager.window_max;i++)
    {
        
        if (!window_manager.window_list[i]._inuse)
        {
           window_manager.window_list[i]._inuse = 1;
           window_manager.window_deque = gf2d_list_append(window_manager.window_deque,&window_manager.window_list[i]);
           window_manager.window_list[i].elements = gf2d_list_new();
           return &window_manager.window_list[i];
        }
    }
    return NULL;
}

void gf2d_window_add_element(Window *win,Element *e)
{
    if (!win)return;
    if (!e)return;
    win->elements = gf2d_list_append(win->elements,e);
}

void gf2d_windows_draw_all()
{
    int i,count;
    count = gf2d_list_get_count(window_manager.window_deque);
    for (i = 0; i < count; i++)
    {
        gf2d_window_draw((Window*)gf2d_list_get_nth(window_manager.window_deque,i));
    }
}

/*eol@eof*/