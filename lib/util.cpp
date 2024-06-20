#include "../header/utils.hpp"
#include "../header/bst.hpp"
#include <__iterator/access.h>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>
#include <strings.h>

extern const Color red;
extern const Color green;
extern const Color blue;
extern const Color yellow;
extern const Color black;
extern const Color white;
extern const Color light_grey;
extern const Color dark_grey;
extern const Color lime;
extern const Color cyan;
extern const Color navy;
extern const Color magenta;
extern const Color violet;
extern const Color olive;
extern const Color crimson;
extern const Color gold;
extern const Color silver;
extern const Color beige;
extern const Color pink;

extern const int XDISTANCE;
extern const int YDISTANCE;
extern const int BUTTON_WIDTH;
extern const int BUTTON_HEIGHT;
extern const int INSERT_BUTTON_X;
extern const int DELETE_BUTTON_X;
extern const int CONTAIN_BUTTON_X;
extern const int REFRESH_BUTTON_X;
extern const int QUIT_BUTTON_X;
extern const int INSERT_BUTTON_Y;
extern const int DELETE_BUTTON_Y;
extern const int CONTAIN_BUTTON_Y;
extern const int REFRESH_BUTTON_Y;
extern const int QUIT_BUTTON_Y;

void Util::init(void) {
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0) {
        panic("SDL Error @SDL_Init: %s", SDL_GetError());
    }
    info(InfoLevel::LEVEL1, "Successfully initialized SDL VIDEO subsystem!");
    info(InfoLevel::LEVEL1, "Successfully initialized SDL AUDIO subsystem!");
    info(InfoLevel::LEVEL1, "Successfully initialized SDL TIMER subsystem!");
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
        info(InfoLevel::LEVEL1, "Failed @SDL_SetHint: %s", SDL_GetError());
    }

    window = SDL_CreateWindow(
        "Binary Search Tree - Developed by Wang, Junzhe",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT,
        SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );
    assertf(window != NULL, "SDL Error @SDL_CreateWindow: %s", SDL_GetError());
    info(InfoLevel::LEVEL1, "Successfully created SDL window!");

    renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED 
        | SDL_RENDERER_PRESENTVSYNC
    );
    assertf(renderer != NULL, "SDL Error @SDL_CreateRenderer: %s", SDL_GetError);
    info(InfoLevel::LEVEL1, "Successfully created SDL renderer!");
    
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
    SDL_RenderClear(renderer);
    
    int IMG_Flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF | IMG_INIT_WEBP;
    int IMG_Init_Flags = IMG_Init(IMG_Flags);
    if (IMG_Flags != (IMG_Init_Flags & IMG_Flags)) {
        panic("SDL Error @IMG_Init: %s", IMG_GetError());
    }
    info(InfoLevel::LEVEL1, "Successfully initialized SDL IMG subsystem!");

    if (TTF_Init() == -1) {
        panic("SDL Error @TTF_Init: %s", TTF_GetError());
    }
    info(InfoLevel::LEVEL1, "Successfully initialized SDL TTF subsystem!");

    char fontname[1024];
    memset(fontname, 0, 1024);
    snprintf(fontname, sizeof(fontname), "UbuntuMono-Regular.ttf");
    this->loadfont(fontname);

    SDL_StartTextInput();
}
void Util::quit(void) {
    SDL_StopTextInput();

    TTF_CloseFont(font);
    font = nullptr;
    info(InfoLevel::LEVEL1, "Successfully closed font!");

    SDL_DestroyRenderer(renderer);
    renderer = nullptr;
    info(InfoLevel::LEVEL1, "Successfully closed renderer!");

    SDL_DestroyWindow(window);
    window = nullptr;
    info(InfoLevel::LEVEL1, "Successfully closed window!");

    TTF_Quit();
    info(InfoLevel::LEVEL1, "Successfully quitted TTF subsystem!");
    IMG_Quit();
    info(InfoLevel::LEVEL1, "Successfully quitted IMG subsystem!");
    SDL_Quit();
    info(InfoLevel::LEVEL1, "Successfully quitted SDL system!");
}
void Util::loadfont(const char * fontname) {
    assertf(fontname != nullptr, "");
    font = TTF_OpenFont(fontname, FONT_PIXEL);
    assertf(font != nullptr, "Error @TTF_OpenFont: %s", TTF_GetError());
    info(InfoLevel::LEVEL1, "Successfully loaded the font %s", fontname);
}

void Util::write(const char * text, const int x, const int y) {
    assertf(text != nullptr, "");
    assertf(text[0] != '\0', "");
    SDL_SetRenderDrawColor(renderer, black.r, black.g, black.b, black.a);
    Surface * surface = TTF_RenderText_Solid(font, text, black);
    assertf(surface != nullptr, "");
    Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    assertf(texture != nullptr, "");
     Rect rect = {
        x, y,
        0, 0,
    };
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    assertf(rect.w > 0, "");
    assertf(rect.h > 0, "");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void Util::write(const char * text, const int x, const int y, const Color * color) {
    if (!color) {
        color = &black;
    }
    Surface * surface = TTF_RenderText_Solid(font, text, *color);
    assertf(surface != nullptr, "");
    Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    assertf(texture != nullptr, "");
     Rect rect = {
        x, y,
        0, 0,
    };
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    assertf(rect.w > 0, "");
    assertf(rect.h > 0, "");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void Util::write(const char * text, const int x, const int y, const Color * fg, const Color * bg) {
    if (!fg) {
        fg = &black;
    }
    if (!bg) {
        bg = &white;
    }
    Surface * surface = TTF_RenderText_Shaded(font, text, *fg, *bg);
    assertf(surface != nullptr, "");
    Texture * texture = SDL_CreateTextureFromSurface(renderer, surface);
    assertf(texture != nullptr, "");
     Rect rect = {
        x, y,
        0, 0,
    };
    SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
    assertf(rect.w > 0, "");
    assertf(rect.h > 0, "");
    SDL_RenderCopy(renderer, texture, nullptr, &rect);

    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);
}
void Util::clear_screen(void) {
    SDL_SetRenderDrawColor(renderer, white.r, white.g, white.b, white.a);
    SDL_RenderClear(renderer);
}
void Util::draw_point(const int x, const int y) {
    const Color * color = &black;
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderDrawPoint(renderer, x, y);
}
void Util::draw_point(const int x, const int y, const Color * color) {
    if (!color) {
        color = &black;
    };
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderDrawPoint(renderer, x, y);
}
void Util::draw_line(const int x1, const int y1, const int x2, const int y2) {
    const Color * color = &black;
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
void Util::draw_line(const int x1, const int y1, const int x2, const int y2, const Color * color) {
    if (!color) {
        color = &black;
    }
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
}
void Util::draw_rect(const int x, const int y, const int w, const int h) {
    const Color * color = &black;
    Rect rect = {
        x, y,
        w, h,
    };
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderDrawRect(renderer, &rect);
}
void Util::draw_rect(const int x, const int y, const int w, const int h, const Color * color) {
    if (!color) {
        color = &black;
    };
    Rect rect = {
        x, y,
        w, h,
    };
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderDrawRect(renderer, &rect);
}
void Util::draw_solid_rect(const int x, const int y, const int w, const int h) {
    const Color * color = &black;
    Rect rect = {
        x, y,
        w, h,
    };
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderFillRect(renderer, &rect);
}
void Util::draw_solid_rect(const int x, const int y, const int w, const int h, const Color * color) {
    if (!color) {
        color = &black;
    }
    Rect rect = {
        x, y,
        w, h,
    };
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    SDL_RenderFillRect(renderer, &rect);
}
void Util::draw_circle(const int x, const int y, const int r) {
    const Color * color = &black;
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    const int NPOINTS = 360;
    Point points[NPOINTS];
    for (int i = 0; i < NPOINTS; i++) {
        double angle = 2.0 * M_PI * i / NPOINTS;
        points[i].x = (int) (x + r * cos(angle));
        points[i].y = (int) (y + r * sin(angle));
    }
    SDL_RenderDrawPoints(renderer, points, NPOINTS);
}
void Util::draw_circle(const int x, const int y, const int r, const Color * color) {
    if (!color) {
        color = &black;
    }
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    const int NPOINTS = 360;
    Point points[NPOINTS];
    for (int i = 0; i < NPOINTS; i++) {
        double angle = 2.0 * M_PI * i / NPOINTS;
        points[i].x = (int) (x + r * cos(angle));
        points[i].y = (int) (y + r * sin(angle));
    }
    SDL_RenderDrawPoints(renderer, points, NPOINTS);
}
void Util::draw_solid_circle(const int x, const int y, const int r) {
    const Color * color = &black;
    const int NPOINTS = 360;
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    for (int i = 0; i < NPOINTS / 2; i++) {
        
        double angle1 = 2.0 * M_PI * i / NPOINTS;
        int x1 = (int) (x + r * cos(angle1));
        int y1 = (int) (y + r * sin(angle1));
        
        double angle2 = 2.0 * M_PI * (NPOINTS - i) / NPOINTS;
        int y2 = (int) (y + r * sin(angle2));
        int x2 = (int) (x + r * cos(angle2));
        
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}
void Util::draw_solid_circle(const int x, const int y, const int r, const Color * color) {
    if (!color) {
        color = &black;
    }
    const int NPOINTS = 360;
    SDL_SetRenderDrawColor(renderer, color->r, color->g, color->b, color->a);
    for (int i = 0; i < NPOINTS / 2; i++) {
        
        double angle1 = 2.0 * M_PI * i / NPOINTS;
        int x1 = (int) (x + r * cos(angle1));
        int y1 = (int) (y + r * sin(angle1));
        
        double angle2 = 2.0 * M_PI * (NPOINTS - i) / NPOINTS;
        int y2 = (int) (y + r * sin(angle2));
        int x2 = (int) (x + r * cos(angle2));
        
        SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
    }
}
void Util::set_clipboard(const char * text) {
    int ret = SDL_SetClipboardText(text);
    assertf(ret == 0, "Error @sdl2_set_clipboard");
}
char * Util::get_clipboard(void) {
    // This return value has to be manually freed.
    char * ret = SDL_GetClipboardText();
    assertf(ret != nullptr, "Error @sdl2_get_clipboard");
    return ret;
}
ButtonStatus Util::button_status(const int x, const int y) {
    ButtonStatus status = ButtonStatus::OUTSIDE;
    if (x >= INSERT_BUTTON_X && x <= INSERT_BUTTON_X + BUTTON_WIDTH) {
        if (y >= INSERT_BUTTON_Y && y <= INSERT_BUTTON_Y + BUTTON_HEIGHT) {
            status = ButtonStatus::INSERT;
            goto end_;
        }
    }
    if (x >= DELETE_BUTTON_X && x <= DELETE_BUTTON_X + BUTTON_WIDTH) {
        if (y >= DELETE_BUTTON_Y && y <= DELETE_BUTTON_Y + BUTTON_HEIGHT) {
            status = ButtonStatus::DELETE;
            goto end_;
        }
    }
    if (x >= CONTAIN_BUTTON_X && x <= CONTAIN_BUTTON_X + BUTTON_WIDTH) {
        if (y >= CONTAIN_BUTTON_Y && y <= CONTAIN_BUTTON_Y + BUTTON_HEIGHT) {
            status = ButtonStatus::HASVAL;
            goto end_;
        }
    }
    if (x >= REFRESH_BUTTON_X && x <= REFRESH_BUTTON_X + BUTTON_WIDTH) {
        if (y >= REFRESH_BUTTON_Y && y <= REFRESH_BUTTON_Y + BUTTON_HEIGHT) {
            status = ButtonStatus::REFRESH;
            goto end_;
        }
    }
    if (x >= QUIT_BUTTON_X && x <= QUIT_BUTTON_X + BUTTON_WIDTH) {
        if (y >= QUIT_BUTTON_Y && y <= QUIT_BUTTON_Y + BUTTON_HEIGHT) {
            status = ButtonStatus::QUIT;
            goto end_;
        }
    }
end_:
    return status;
}
void Util::draw_button(const char * text, const int x, const int y, const int w, const int h) {    
    const Color * color = &black;
    SDL_Rect rect = {
        x, y,
        w, h
    };
    SDL_SetRenderDrawColor(
        renderer,
        color->r, 
        color->g, 
        color->b, 
        color->a
    );
    SDL_RenderFillRect(
        renderer,
        &rect
    );
    write(text, x + 2, y, &white);
}
void Util::draw_button(const char * text, const int x, const int y, const int w, const int h, const Color * color) {    
    if (!color) {
        color = &black;
    }
    SDL_Rect rect = {
        x, y,
        w, h
    };
    SDL_SetRenderDrawColor(
        renderer,
        color->r, 
        color->g, 
        color->b, 
        color->a
    );
    SDL_RenderFillRect(
        renderer,
        &rect
    );
    write(text, x + 2, y, &black);
}
void Util::refresh(void) {
    bool done = false;
    bool success = false;
    bool finished = false;
    Event event;

    Color insert_color  = light_grey;
    Color delete_color  = light_grey;
    Color contain_color = light_grey;
    Color refresh_color = light_grey;
    Color quit_color    = light_grey;

    Tree tree;
    TreeStatus status = TreeStatus::INIT;
    char buf[256];
    bzero(buf, sizeof(buf));

    do {
        SDL_PumpEvents();
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                done = true;
            }
            else if (event.type == SDL_TEXTINPUT) {
                if (buf[254] == '\0') {
                    strncat(buf, event.text.text, 1);
                }
            }
            else if (event.type == SDL_MOUSEMOTION || event.type == SDL_MOUSEBUTTONUP || event.type == SDL_MOUSEBUTTONDOWN) {
                int x;
                int y;
                SDL_GetMouseState(&x, &y);
                ButtonStatus bottom = button_status(x, y);
                switch (bottom) {
                    case ButtonStatus::INSERT:
                    {
                        insert_color = dark_grey;
                        delete_color = light_grey;
                        contain_color = light_grey;
                        refresh_color = light_grey;
                        quit_color = light_grey;
                        if (event.type == SDL_MOUSEBUTTONUP && status == TreeStatus::PROC) 
                        {
                            status = TreeStatus::INSERT;
                        }
                    } break;

                    case ButtonStatus::DELETE:
                    {
                        insert_color = light_grey;
                        delete_color = dark_grey;
                        contain_color = light_grey;
                        refresh_color = light_grey;
                        quit_color = light_grey;
                        if (event.type == SDL_MOUSEBUTTONUP && status == TreeStatus::PROC) {
                            status = TreeStatus::DELETE;
                        }
                    } break;

                    case ButtonStatus::HASVAL:
                    {
                        insert_color = light_grey;
                        delete_color = light_grey;
                        contain_color = dark_grey;
                        refresh_color = light_grey;
                        quit_color = light_grey;
                        if (event.type == SDL_MOUSEBUTTONUP && status == TreeStatus::PROC) {
                            status = TreeStatus::HASVAL;
                        }
                    } break;
                    
                    case ButtonStatus::REFRESH:
                    {
                        insert_color = light_grey;
                        delete_color = light_grey;
                        contain_color = light_grey;
                        refresh_color = dark_grey;
                        quit_color = light_grey;
                        if (event.type == SDL_MOUSEBUTTONUP && status != TreeStatus::INIT) {
                            bzero(buf, sizeof(buf));
                            finished = false;
                            status = TreeStatus::PROC;
                        }
                    } break;
                    
                    case ButtonStatus::QUIT:
                    {
                        insert_color = light_grey;
                        delete_color = light_grey;
                        contain_color = light_grey;
                        refresh_color = light_grey;
                        quit_color = dark_grey;
                        if (event.type == SDL_MOUSEBUTTONUP) {
                            done = true;
                        }
                    } break;

                    default:
                    {
                        insert_color = light_grey;
                        delete_color = light_grey;
                        contain_color = light_grey;
                        refresh_color = light_grey;
                        quit_color = light_grey;
                    } break;
                }
            }
            else if (event.type == SDL_KEYDOWN && event.key.repeat == 0) {
                switch (event.key.keysym.sym) {
                    case SDLK_UP:
                    case SDLK_DOWN:
                    case SDLK_LEFT:
                    case SDLK_RIGHT:
                    {
                    } break;

                    case SDLK_RETURN:
                    {
                        switch (status) {
                            case TreeStatus::INIT:
                            {
                                char * endptr;
                                int val = (int) std::strtol(buf, &endptr, 10);
                                if (endptr == buf || *endptr != '\0') {
                                }
                                else {
                                    tree.insert(val);
                                    status = TreeStatus::PROC;
                                }
                            } break;

                            case TreeStatus::INSERT:
                            {
                                char * endptr;
                                int val = (int) std::strtol(buf, &endptr, 10);
                                if (endptr == buf || *endptr != '\0') {
                                    success = false;
                                }
                                else {
                                    tree.insert(val);
                                    success = true;
                                }
                                finished = true;
                            } break;

                            case TreeStatus::DELETE:
                            {
                                char * endptr;
                                int val = (int) std::strtol(buf, &endptr, 10);
                                if (endptr == buf || *endptr != '\0') {
                                    success = false;
                                }
                                else {
                                    if (tree.search(val)) {
                                        tree.remove(val);
                                        success = true;
                                    }
                                    else {
                                        success = false;
                                    }
                                }
                                finished = true;
                            } break;

                            case TreeStatus::HASVAL:
                            {
                                char * endptr;
                                int val = (int) std::strtol(buf, &endptr, 10);
                                if (endptr == buf || *endptr != '\0') {
                                    success = false;
                                }
                                else {
                                    success = tree.search(val);
                                }
                                finished = true;
                            } break;

                            default:
                            {
                            } break;
                        }
                        bzero(buf, sizeof(buf));
                    } break;

                    case SDLK_SPACE:
                    {
                    } break;

                    case SDLK_ESCAPE:
                    {
                    } break;

                    case SDLK_BACKSPACE:
                    {
                        int len = std::strlen(buf);
                        if (len > 0) {
                            buf[len - 1] = '\0';
                        }
                    } break;

                    case SDLK_LCTRL:
                    case SDLK_RCTRL:
                    {
                    } break;

                    case SDLK_LSHIFT:
                    case SDLK_RSHIFT:
                    {
                    } break;

                    case SDLK_CAPSLOCK:
                    {
                    } break;

                    case SDLK_F1:
                    case SDLK_F2:
                    case SDLK_F3:
                    case SDLK_F4:
                    case SDLK_F5:
                    case SDLK_F6:
                    case SDLK_F7:
                    case SDLK_F8:
                    case SDLK_F9:
                    case SDLK_F10:
                    case SDLK_F11:
                    case SDLK_F12:
                    case SDLK_F13:
                    case SDLK_F14:
                    case SDLK_F15:
                    {
                    } break;
                }
            }
        }

        clear_screen();

        switch (status) {
            case TreeStatus::INIT:
            {
                const char * s = "Please enter an integer for the root:";
                write(s, 20, 20);
            } break;

            case TreeStatus::PROC:
            {
                const char * s = "Please click one of the buttons below.";
                write(s, 20, 20);
            } break;

            case TreeStatus::INSERT:
            {
                const char * s = "Please enter the integer you wish to insert:";
                write(s, 20, 20);
                if (!finished) {
                    break;
                }
                if (success) {
                    const char * sucmsg = "Insertion succeeded!";
                    write(sucmsg, 20, 50);
                }
                else {
                    const char * errmsg = "Insertion failed!";
                    write(errmsg, 20, 50, &red);
                }
            } break;

            case TreeStatus::DELETE:
            {
                const char * s = "Please enter the integer you wish to delete:";
                write(s, 20, 20);
                if (!finished) {
                    break;
                }
                if (success) {
                    const char * sucmsg = "Deletion succeeded!";
                    write(sucmsg, 20, 50);
                }
                else {
                    const char * errmsg = "Deletion failed!";
                    write(errmsg, 20, 50, &red);
                }
            } break;

            case TreeStatus::HASVAL:
            {
                const char * s = "Please enter the integer you wish to check in the tree:";
                write(s, 20, 20);
                if (!finished) {
                    break;
                }
                if (success) {
                    const char * sucmsg = "Integer exists!";
                    write(sucmsg, 20, 50);
                }
                else {
                    const char * errmsg = "Integer missing!";
                    write(errmsg, 20, 50, &red);
                }
            } break;

            default:
            {
            } break;
        }

        if (buf[0] != '\0') {
            write(buf, 50, 80);
        }
        draw_button("insert", INSERT_BUTTON_X, INSERT_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, &insert_color);
        draw_button("delete", DELETE_BUTTON_X, DELETE_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, &delete_color);
        draw_button("contain", CONTAIN_BUTTON_X, CONTAIN_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, &contain_color);
        draw_button("refresh", REFRESH_BUTTON_X, REFRESH_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, &refresh_color);
        draw_button("quit", QUIT_BUTTON_X, QUIT_BUTTON_Y, BUTTON_WIDTH, BUTTON_HEIGHT, &quit_color);
        tree.breadth_first_traversal(1000, 650);
        SDL_RenderPresent(renderer);
    } while (!done);
}



void info(InfoLevel level, const char * fmt, ...) {
    switch (level) {
        case InfoLevel::LEVEL1:
        {
            fprintf(stderr, "\e[1;37m");
        } break;

        case InfoLevel::LEVEL2:
        {
            fprintf(stderr, "\e[1;32m");
        } break;

        case InfoLevel::LEVEL3:
        {
            fprintf(stderr, "\e[1;33m");
        } break;

        case InfoLevel::LEVEL4:
        {
            fprintf(stderr, "\e[1;35m");
        } break;
    }
    time_t now = time(NULL);
    if (now == (time_t) -1) {
        exit(2);
    }

    struct tm * localtm = localtime(&now);
    if (!localtm) {
        exit(3);
    }

    char * timestr = asctime(localtm);
    if (!timestr) {
        exit(4);
    }

    fprintf(stderr, "\t%s\t\e[0m", timestr);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n\n");
}

void panic(const char * fmt, ...) {
    fprintf(stderr, "\e[1;31m");
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    va_end(args);
    fprintf(stderr, "\n\e[0m");
    exit(EXIT_FAILURE);
}

void errorf(const char * file, const int line, const char * fmt, ...) {
    fprintf(stderr, "%s:%d: \e[1;31m", file, line);
    va_list args;
    va_start(args, fmt);
    vfprintf(stderr, fmt, args);
    fprintf(stderr, "\n\e[0m");
    va_end(args);
    exit(EXIT_FAILURE);
}


