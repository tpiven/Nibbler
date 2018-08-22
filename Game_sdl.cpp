#include "Game_sdl.hpp"
#include "TextureManager.hpp"
#include "GameObj_sdl.hpp"
#include "Map.hpp"

GameObj_sdl  *player;
Map* map;


SDL_Renderer* Game_sdl::renderer = nullptr;

Game_sdl::Game_sdl() :_end_game(false), _cnt(0) {
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
    renderer = SDL_CreateRenderer(_window, -1, 0);
    if (!renderer) {
        std::cout << "Trouble wih render" << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    player = new GameObj_sdl("/Users/kmykhail/Desktop/Nibbler/Picture/dirt.png", 0, 0);
    //renderMap();
    map = new Map();
}

void Game_sdl::handleEvent() {
    SDL_PollEvent(&_event);
    if (_event.type == SDL_QUIT)
        _end_game = true;
}

void Game_sdl::update() {
    player->Update();
}

void Game_sdl::renderMap() {
    map = new Map();
    map->DrawMap();
}

void Game_sdl::render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    player->Render();
    SDL_RenderPresent(renderer);
}

void Game_sdl::clean() {
    SDL_DestroyWindow(_window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    std::cout << "Clened" << std::endl;
}


bool Game_sdl::running() { return _end_game; }

Game_sdl::~Game_sdl() {}
