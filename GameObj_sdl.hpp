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
    char _direction;

    SDL_Texture *_objTexture;
    SDL_Rect    scrR;
    std::vector<int> _corXY;
    std::vector<SDL_Texture*> snakeTexture;
public:
    GameObj_sdl(const char *texture, int x, int y, char direction);
    ~GameObj_sdl();
    void    Update();
    void    Render();
    void    setDirection(char dir);
    bool  _turn;
};


#endif //NIBBLER_GAMEOBJ_SDL_HPP
