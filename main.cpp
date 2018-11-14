
#include "Game_sdl.hpp"

void    obj_staff(Game_sdl &obj){
    obj.handleEvent();
    obj.update();
    obj.render();
}

int main(int argc, char* argv[]) {
    int const FPS = 60;
    int const frameDealy = 500 / FPS;

    uint32_t  frameStart;
    int frameTime;

    Game_sdl obj;
    obj.init("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1440, 1072, 0);
    while(!obj.running()){

        frameStart = SDL_GetTicks();
        obj_staff(obj);
        frameTime = SDL_GetTicks() - frameStart;
        if (frameDealy > frameTime)
            SDL_Delay(frameDealy - frameTime);
    }
    obj.clean();
    return 0;
}

