#pragma once
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <cstdio>
#include <cstdlib>
#include <cstdbool>
#include <cstring>
#include <cmath>
#include <climits>
#include <cstdarg>
#include <ctime>
#include <string>

#define error(...) errorf(__FILE__, __LINE__, __VA_ARGS__)
#define assertf(expr, ...)                                  \
    do {                                                    \
        if (!(expr)) error(__VA_ARGS__);                    \
    } while (0)

typedef char i8;
typedef unsigned char u8;
typedef short i16;
typedef unsigned short u16;
typedef int i32;
typedef unsigned int u32;
typedef long i64;
typedef unsigned long u64;

typedef TTF_Font Font;
typedef SDL_Rect Rect;
typedef SDL_Point Point;
typedef SDL_Event Event;
typedef SDL_Color Color;
typedef SDL_Cursor Cursor;
typedef SDL_Window Window;
typedef SDL_Surface Surface;
typedef SDL_Texture Texture;
typedef SDL_Renderer Renderer;

enum class InfoLevel {
    LEVEL1,
    LEVEL2,
    LEVEL3,
    LEVEL4,
};
enum class ButtonStatus {
    OUTSIDE,
    INSERT,
    DELETE,
    HASVAL,
    REFRESH,
    QUIT,
};
enum class TreeStatus {
    INIT,
    PROC,
    INSERT,
    DELETE,
    HASVAL,
};


void info(InfoLevel level, const char * fmt, ...);
void panic(const char * fmt, ...);
void errorf(const char * file, const int line, const char * fmt, ...);

class Util {
private:
    Font * font;
    Window * window;
    Renderer * renderer;
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    const int FONT_PIXEL = 20;
    
    std::string program;

public:
    Util() : font(nullptr), window(nullptr), renderer(nullptr), 
            SCREEN_WIDTH(1280) , SCREEN_HEIGHT(720)
    { }

    void init(void);
    void quit(void);
    void loadfont(const char * fontname);
    void write(const char * text, const int x, const int y);
    void write(const char * text, const int x, const int y, const Color * color);
    void write(const char * text, const int x, const int y, const Color * fg, const Color * bg);
    void clear_screen(void);
    void draw_line(const int x1, const int y1, const int x2, const int y2);
    void draw_line(const int x1, const int y1, const int x2, const int y2, const Color * color);
    void draw_rect(const int x, const int y, const int w, const int h);
    void draw_rect(const int x, const int y, const int w, const int h, const Color * color);
    void draw_solid_rect(const int x, const int y, const int w, const int h);
    void draw_solid_rect(const int x, const int y, const int w, const int h, const Color * color);
    void draw_circle(const int x, const int y, const int r);
    void draw_circle(const int x, const int y, const int r, const Color * color);
    void draw_solid_circle(const int x, const int y, const int r);
    void draw_solid_circle(const int x, const int y, const int r, const Color * color);
    void draw_point(const int x, const int y);
    void draw_point(const int x, const int y, const Color * color);
    void set_clipboard(const char * text);
    char * get_clipboard(void);
    ButtonStatus button_status(const int x, const int y);
    void draw_button(const char * text, const int x, const int y, const int w, const int h);
    void draw_button(const char * text, const int x, const int y, const int w, const int h, const Color * color);    
    void refresh(void);
};

