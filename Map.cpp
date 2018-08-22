//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#include "Map.hpp"
#include "TextureManager.hpp"

//0 grass
//1 border
//2 water
//3 rock

int lvl1[20][25] = {
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,3,3,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,2,2,2,2,2,2,2,2,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,2,2,2,2,0,2,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
};

Map::Map() {
    dirt = TextureManager::LoadTexture("/Users/kmykhail/Desktop/Nibbler/Picture/dirt.png");
    grass = TextureManager::LoadTexture("/Users/kmykhail/Desktop/Nibbler/Picture/grass2.png");
    water = TextureManager::LoadTexture("/Users/kmykhail/Desktop/Nibbler/Picture/water.png");
    LoadMap(lvl1);
    src.x = src.y = 0;
    src.w = dest.w = 32;//256*256
    src.h = dest.h = 32;

    dest.x= dest.y = 0;
}

Map::~Map() {}

void Map::LoadMap(int arr[20][25])  {
    for (int row = 0; row < 20 ; ++row) {
        for (int column = 0; column < 25; ++column) {
            map[row][column] = arr[row][column];
        }
    }

    for (int i = 0; i < 20; ++i) {
        for (int j = 0; j < 25; ++j) {
            std::cout << map[i][j] << ",";
        }
        std::cout << std::endl;
    }

    std::cout << "STOP" << std::endl;
}

void Map::DrawMap() {
    int type = 0;
    //TextureManager::Draw(grass, src, dest);
    for (int row = 0; row < 20; ++row) {
        //dest.y = row * 32;
        for (int column = 0; column < 25 ; ++column) {
            type = map[row][column];
            dest.x = column * 32;
            dest.y = row * 32;
            switch (type){
                case 0:
                    TextureManager::Draw(grass, src, dest);
                    break;
                case 2:
                    TextureManager::Draw(water, src, dest);
                    break;
                case 3:
                    TextureManager::Draw(dirt, src, dest);
                    break;
                default:
                    break;
            }
            /*if (!type) {
                TextureManager::Draw(grass, src, dest);
            }
            else if (type == 2){
                TextureManager::Draw(water, src, dest);
            }
            else if (type == 3)
                TextureManager::Draw(dirt, src, dest);*/
            std::cout << type << ",";
        }
        std::cout << std::endl;
    }
    /*
    for (int i = 0; i < 20 ; ++i) {
        dest.x = 0;
        for (int j = 0; j < 25; ++j) {
            type = map[i][j];

            dest.x = j* 32;
            if (!type)
                TextureManager::Draw(dirt, src, dest);
            else if (type == 2)
                TextureManager::Draw(dirt, src, dest);
            else if (type == 3)
                TextureManager::Draw(dirt, src, dest);
        }
        dest.y += 32;
    }
*/
}