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
    int const FPS = 60;
    int const frameDealy = 1000 / FPS;

    uint32_t  frameStart;
    int frameTime;

    Game_sdl obj;
    obj.init("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 1072, 0);
    while(!obj.running()){

        //frameStart = SDL_GetTicks();

        obj.handleEvent();
        obj.update();
        obj.render();
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDealy > frameTime)
            SDL_Delay(frameDealy - frameTime);
    }
    obj.clean();
    return 0;
}