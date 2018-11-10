//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#ifndef NIBBLER_MAP_HPP
#define NIBBLER_MAP_HPP

#include "Game_sdl.hpp"

//int g_weight;
//int g_height;

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

    SDL_Texture *bloc_left_gray;
    SDL_Texture *bloc_right_gray;
    SDL_Texture *bloc_up_down_gray;

    SDL_Texture *bloc_center_white;
    SDL_Texture *bloc_left_white;
    SDL_Texture *bloc_right_white;
    SDL_Texture *bloc_up_white;
    SDL_Texture *bloc_down_white;
    SDL_Texture *bloc_turn3_white;
    SDL_Texture *bloc_turn4_white;
    SDL_Texture *bloc_turn1_white;
    SDL_Texture *bloc_turn2_white;


    SDL_Texture *Level1_map;



    //int map[67][90];
    int (*_map)[67][90];
public:
    Map(int w, int h);
    ~Map();
    void LoadMap();
    void DrawMap();
    void    setMap(int x, int y);
    int     *getMap();
};


#endif //NIBBLER_MAP_HPP
