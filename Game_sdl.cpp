#include "Game_sdl.hpp"

SDL_Texture *platerTex;
SDL_Rect scrR, destR;

Game_sdl::Game_sdl() :_end_game(false), _cnt(0) {
    //init_window();
}

void Game_sdl::init(const char *title, int x, int y, int w, int h, bool fullscr) {
    int flags = SDL_WINDOW_SHOWN;
    if (fullscr)
        flags = SDL_WINDOW_FULLSCREEN;
    if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
        std::cout << "Trouble with init SDL" << std::endl;
        return;
    }
    _window = SDL_CreateWindow(
            title,
            x,
            y,
            w,
            h,
            flags
    );
    if (!_window) {
        std::cout << "Error Window: " << &SDL_Error << std::endl;
        return;
    }
    _renderer = SDL_CreateRenderer(_window, -1, 0);
    if (!_renderer) {
        std::cout << "Trouble wih render" << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(_renderer, 230, 0, 0, 255);
    SDL_Surface *tmp_surface = IMG_Load("/Users/kmykhail/Desktop/Nibbler/solid.png");
    platerTex = SDL_CreateTextureFromSurface(_renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);
}


void Game_sdl::handleEvent() {
    SDL_PollEvent(&_event);
    if (_event.type == SDL_QUIT || _event.key.keysym.sym == SDLK_ESCAPE)
        _end_game = true;
}

void Game_sdl::update() {
    _cnt++;
    destR.h = 50;
    destR.w = 50;

    std::cout << _cnt << std::endl;
}

void Game_sdl::render() {
    SDL_RenderClear(_renderer);
    SDL_RenderCopy(_renderer, platerTex, NULL, &destR);
    SDL_RenderPresent(_renderer);
}

void Game_sdl::clean() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(_renderer);
    SDL_Quit();
    std::cout << "Clened" << std::endl;
}


bool Game_sdl::running() { return _end_game; }

/*void Game_sdl::init_window() {
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Window *window = nullptr;
    SDL_Renderer *renderer = nullptr;
    window = SDL_CreateWindow(
            "Nibbler",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            800,
            600,
            SDL_WINDOW_SHOWN
    );
    renderer = SDL_CreateRenderer(window, -1, 0);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);
    SDL_Delay(3000);
    SDL_Quit();
}*/

Game_sdl::~Game_sdl() {}

//void Game_sdl::init_game() {
//    SDL_Event key;
//    while(SDL_PollEvent( &key) != 0){
//        if (key.type == SDL_QUIT)
//            _end_game = true;
//    }
//}