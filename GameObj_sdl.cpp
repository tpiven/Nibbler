//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#include "GameObj_sdl.hpp"
#include "TextureManager.hpp"

GameObj_sdl::GameObj_sdl(const char *texture, int x, int y) {
    _objTexture = TextureManager::LoadTexture(texture);
    xpos = x;
    ypos = y;
}

void GameObj_sdl::Update() {

    xpos++;
    ypos++;

    scrR.h = 10;
    scrR.w = 10;
    scrR.x = 0;
    scrR.y = 0;

    destR.x = xpos;
    destR.y = ypos;
    destR.w = scrR.w * 2;
    destR.h = scrR.h * 2;
}

void GameObj_sdl::Render() {
    SDL_RenderCopy(Game_sdl::renderer, _objTexture, &scrR, &destR);
}