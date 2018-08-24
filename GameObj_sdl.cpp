//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#include "GameObj_sdl.hpp"
#include "TextureManager.hpp"

GameObj_sdl::GameObj_sdl(const char *texture, int x, int y) {
    //_objTexture = TextureManager::LoadTexture(texture);
    /*SDL_Surface *tmp_surface = IMG_Load(texture);
    _objTexture = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);*/
    SDL_Surface * tmp_surface = IMG_Load(texture);
    snakeTexture.push_back(SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface));
    snakeTexture.push_back(snakeTexture.back());
    snakeTexture.push_back(snakeTexture.back());
    SDL_FreeSurface(tmp_surface);

    xpos = 48;
    ypos = 16;
    body.push_back(0);//head
    body.push_back(body.back() + 1);
    body.push_back(body.back() + 1);
}

void GameObj_sdl::Update() {

    xpos++;
    //ypos++;

    scrR.h = 16;
    scrR.w = 16;
    scrR.x = xpos;
    scrR.y = ypos;
    //destR.x = xpos;
    //destR.y = ypos;
    //destR.w = scrR.w * 2;
    //destR.h = scrR.h * 2;
}

void GameObj_sdl::Render() {
    SDL_RenderCopy(Game_sdl::renderer, snakeTexture[0], NULL, &scrR);
    scrR.x = 32;
    scrR.y = 16;
    SDL_RenderCopy(Game_sdl::renderer, snakeTexture[1], NULL, &scrR);
    scrR.x = 16;
    scrR.y = 16;
    SDL_RenderCopy(Game_sdl::renderer, snakeTexture[2], NULL, &scrR);
}