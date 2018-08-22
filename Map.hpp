//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#ifndef NIBBLER_MAP_HPP
#define NIBBLER_MAP_HPP

#include "Game_sdl.hpp"

class Map  {
private:
    SDL_Rect src, dest;
    SDL_Texture *dirt;
    SDL_Texture *grass;
    SDL_Texture *water;
    int map[20][25];
public:
    Map();
    ~Map();
    void LoadMap(int arr[20][25]);
    void DrawMap();

};


#endif //NIBBLER_MAP_HPP
