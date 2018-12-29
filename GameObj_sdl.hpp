//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//
#ifndef NIBBLER_GAMEOBJ_SDL_HPP
#define NIBBLER_GAMEOBJ_SDL_HPP

#include "headers.h"
#include "Game_sdl.hpp"
#include "Food.hpp"

class Food;

class GameObj_sdl {
private:
    int xpos;
    int ypos;
    char _direction;
    int high;
    int low;
    int buffVal_y;
    int buffVal_x;
    char _sybBuff;
    int _cnt_block;
    SDL_Texture *_objTexture;
    SDL_Rect    scrR;
    std::vector<int> _corXY;
    std::map<int, std::pair<int, int>>_cors;
    std::map<int, SDL_Texture*> snakeTexture;
    std::string    _fr_blockX;//first block of snake
    std::pair<int , int> _head_dots[2];

public:
    GameObj_sdl(const char *texture, int x, int y, int (*)[67][90], char direction);
    ~GameObj_sdl();
    void    Update();
    void    Render(int (*&)[67][90], std::shared_ptr<Food> & food);
    void    setDirection(char dir);
    char    getDirection() const;
    void    setSymBuff(char sym);
    char    getSymBuff() const;
    std::pair<int, int >getHighLow() const;
    void get_cor(size_t cnt_cors);
    void    moveOnX(size_t &);
    void    moveOnY(size_t &);
    void    turnOnX(size_t &);
    void    turnOnY(size_t &);
    bool AreSnakeBlocksEqual(int);
    bool  _turn;
    void    grow(int (*m_map)[67][90], std::shared_ptr<Food> & food, size_t cnt_cors);//grow body snake
    bool touch(int x, int y, int z, int w, int a, int b);
    void rotate();
};


#endif //NIBBLER_GAMEOBJ_SDL_HPP


