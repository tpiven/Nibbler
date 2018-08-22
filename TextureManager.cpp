//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#include "TextureManager.hpp"

TextureManager::TextureManager() {}

TextureManager::~TextureManager() {}

SDL_Texture* TextureManager::LoadTexture(const char *filename) {
    std::cout << "Filename: " << filename << std::endl;
    SDL_Surface *tmp_surface = IMG_Load(filename);
    SDL_Texture * texture = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
    return  texture;
}

void TextureManager::Draw(SDL_Texture *texture, SDL_Rect src, SDL_Rect dst) {
    SDL_RenderCopy(Game_sdl::renderer, texture, &src, &dst);
}