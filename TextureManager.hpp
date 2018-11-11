//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#ifndef NIBBLER_TEXTUREMANAGER_HPP
#define NIBBLER_TEXTUREMANAGER_HPP

#include "Game_sdl.hpp"

class TextureManager {
public:
    TextureManager();
    ~TextureManager();
    static SDL_Texture* LoadTexture(const char *filename);
    static void Draw(SDL_Texture * texture, SDL_Rect dst);
};


#endif //NIBBLER_TEXTUREMANAGER_HPP
