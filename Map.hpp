//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#ifndef NIBBLER_MAP_HPP
#define NIBBLER_MAP_HPP

#include "Game_sdl.hpp"

class Map  {
private:
    SDL_Rect src, dest;
    SDL_Texture *grass;
    SDL_Texture *grass_bloc_mod;
    //wall_texture
    SDL_Texture *wal_left_dirt;
    SDL_Texture *wal_up_dirt;
    SDL_Texture *wal_right_dirt;
    SDL_Texture *wal_down_dirt;
    SDL_Texture *wal_turn1_dirt;
    SDL_Texture *wal_turn2_dirt;
    SDL_Texture *wal_turn3_dirt;
    SDL_Texture *wal_turn4_dirt;

    SDL_Texture *water;
    //beach_texture
    SDL_Texture *beach_left_water;
    SDL_Texture *beach_up_water;
    SDL_Texture *beach_right_water;
    SDL_Texture *beach_down_water;
    SDL_Texture *beach_turn1_water;
    SDL_Texture *beach_turn2_water;
    SDL_Texture *beach_turn3_water;
    SDL_Texture *beach_turn4_water;

    SDL_Texture *barrel;

    SDL_Texture *road_vert_left;
    SDL_Texture *road_vert_right;
    SDL_Texture *road_gorisont_up;
    SDL_Texture *road_gorisont_down;
    SDL_Texture *road_center;
    int map[67][90];
public:
    Map();
    ~Map();
    void LoadMap(int arr[67][90]);
    void DrawMap();

};


#endif //NIBBLER_MAP_HPP
