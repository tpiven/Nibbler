//#include <iostream>
//# include <OpenGL/gl3.h>
//# include <stdio.h>
//# include <SDL.h>
//# include <SDL_video.h>
//# include <math.h>
//# include <stdbool.h>
//# include <string.h>
//# include <stdlib.h>
//# include "SDL_ttf.h"
//# include "SDL_image.h"
//# include <SDL_keycode.h>

#include "Game_sdl.hpp"

int main(int argc, char* argv[]) {
    Game_sdl obj;
    obj.init("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0);
    while(!obj.running()){
        obj.handleEvent();
        obj.update();
        obj.render();
    }
    obj.clean();
    return 0;
}