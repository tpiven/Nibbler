//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//
#ifndef NIBBLER_GAMEOBJ_SDL_HPP
#define NIBBLER_GAMEOBJ_SDL_HPP

#include "Game_sdl.hpp"

class GameObj_sdl {
private:
    int xpos;
    int ypos;
    SDL_Texture *_objTexture;
    SDL_Rect    scrR, destR;
public:
    GameObj_sdl(const char *texture, int x, int y);
    ~GameObj_sdl();
    void    Update();
    void    Render();
};


#endif //NIBBLER_GAMEOBJ_SDL_HPP
