#ifndef GAME_SDL_HPP
#define GAME_SDL_HPP

#include "SDL.h"
#include "SDL_image.h"
#include <iostream>

class Game_sdl{
private:
    bool _end_game;
    int _cnt;
    int _width;
    int _height;
    SDL_Window *_window;
    SDL_Event    _event;
public:
    Game_sdl();
    ~Game_sdl();

    void    init(const char* title, int x, int y, int w, int h, bool fullscr);
    void    handleEvent();
    void    update();
    void    render();
    void    renderMap();
    void    clean();

    bool    running();
    static  SDL_Renderer *renderer;
};

#endif