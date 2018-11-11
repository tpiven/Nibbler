#ifndef FOOD_HPP
#define FOOD_HPP

#include "headers.h"
#include "TextureManager.hpp"

//int (*)[67][90]


class Food{
private:
    SDL_Texture *_texture_food_lil;
    SDL_Texture *_texture_food_big;
    SDL_Rect    scrR_lil;
    SDL_Rect    scrR_big;
    std::pair<int, int> _cor_lil_food;
    std::pair<int, int> _cor_big_food;
public:
    Food(const char *lil_food, const char *big_food);
    ~Food();
    void    mandatoryFood(int (*)[67][90]);//mandatory food on map
    void    surpriseFood();
    void    DrawFood();
};

#endif