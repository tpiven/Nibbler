#ifndef GAME_SDL_HPP
#define GAME_SDL_HPP

#include "headers.h"
#include "TextureManager.hpp"
#include "Map.hpp"
#include "GameObj_sdl.hpp"
#include "Food.hpp"

class GameObj_sdl;
class Food;

class Game_sdl{
private:
    bool _end_game;
    int _cnt;
    int _width;
    int _height;

    SDL_Window *_window;
    SDL_Event    _event;
    GameObj_sdl  *player;
    //Map* map;
    //Food*   food;
    //std::shared_ptr<GameObj_sdl>player;
    std::shared_ptr<Map> map;
    std::shared_ptr<Food>food;
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
