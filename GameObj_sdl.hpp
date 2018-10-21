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
    int high;
    int low;
    SDL_Texture *_objTexture;
    SDL_Rect    scrR;
    std::vector<int> _corXY;
    std::map<int, std::pair<int, int>>_cors;
    std::map<int, SDL_Texture*> snakeTexture;
    std::string    _fr_blockX;//first block of snake

public:
    GameObj_sdl(const char *texture, int x, int y, char direction);
    ~GameObj_sdl();
    void    Update();
    void    Render();
    void    setDirection(char dir);
    void    moveOnX(size_t &);
    void    moveOnY(size_t &);
    void    turnOnX(size_t &);
    void    turnOnY(size_t &);
    bool    AreSnakeBlocksEqual();
    bool  _turn;

};


#endif //NIBBLER_GAMEOBJ_SDL_HPP
