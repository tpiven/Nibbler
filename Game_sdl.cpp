#include "Game_sdl.hpp"
#include "TextureManager.hpp"
#include "GameObj_sdl.hpp"
#include "Map.hpp"
#include <chrono>
#include <thread>


GameObj_sdl  *player;
Map* map;


SDL_Renderer* Game_sdl::renderer = nullptr;

Game_sdl::Game_sdl() :_end_game(false), _cnt(0) {
}

void Game_sdl::init(const char *title, int x, int y, int w, int h, bool fullscr) {
    _width = w;
    _height = h;
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
    renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        std::cout << "Trouble wih render" << std::endl;
        return;
    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    char path[4096];
    std::string dir = getwd(path);//get_current_dir_name();//macOs stupid
    //char *cwd_buffer = malloc(sizeof(char) * MAX_PATH_NAME);
    //std::string dir =
    std::cout << dir << std::endl;
    size_t  n = dir.rfind('/');
    dir.resize(n);
    player = new GameObj_sdl( (dir + "/Picture/dirt.png").c_str(), 200, 7, 'd');
    map = new Map();
}

void Game_sdl::handleEvent() {
    std::pair<int , int> hl = player->getHighLow();
    char tmp_sym = player->getSymBuff();
    SDL_PollEvent(&_event);
    if (_event.type == SDL_QUIT)
        _end_game = true;
    if (_event.type == SDL_KEYDOWN){
        switch (_event.key.keysym.sym ){
            case SDLK_ESCAPE:
                _end_game = true;
                break;
            case SDLK_w://1
                if (player->getDirection() != 's' && (hl.first == 16 && hl.second == 16)){
                    if (tmp_sym == 'q')
                        player->setDirection('w');
                    else if (tmp_sym != 'q'){
                        player->setDirection(tmp_sym);
                        player->setSymBuff('w');
                    }
                } else if (player->getDirection() != 's' && (hl.first != 16 || hl.second != 16)){
                    tmp_sym = (tmp_sym == 'q') ? 'w' : tmp_sym;
                    player->setDirection(tmp_sym);
                    //if (tmp_sym == 'q'){
                    //    player->setDirection('w');
                    //}
                    /*else {
                        player->setDirection(tmp_sym);
                        tmp_sym = 'q';
                    }*/
                }
                break;
            case SDLK_s://2
                if (player->getDirection() != 'w' && (hl.first == 16 && hl.second == 16)){
                    if (tmp_sym == 'q')
                        player->setDirection('s');
                    else if (tmp_sym != 'q'){
                        player->setDirection(tmp_sym);
                        player->setSymBuff('s');
                    }
                }else if (player->getDirection() != 'w' && (hl.first != 16 || hl.second != 16)){
                    tmp_sym = (tmp_sym == 'q') ? 'w' : tmp_sym;
                    player->setDirection(tmp_sym);
                }
                break;
            case SDLK_d://3
                if (player->getDirection() != 'a' && (hl.first == 16 && hl.second == 16)){
                    if (tmp_sym == 'q')
                        player->setDirection('d');
                    else if (tmp_sym != 'q'){
                        player->setDirection(tmp_sym);
                        player->setSymBuff('d');
                    }
                }else if (player->getDirection() != 'a' && (hl.first != 16 || hl.second != 16)){
                    tmp_sym = (tmp_sym == 'q') ? 'd' : tmp_sym;
                    player->setSymBuff(tmp_sym);
                }
                break;
            case SDLK_a:
                if (player->getDirection() != 'd' && (hl.first == 16 && hl.second == 16)){
                    if (tmp_sym == 'q')
                        player->setDirection('a');
                    else if (tmp_sym != 'q'){
                        player->setDirection(tmp_sym);
                        player->setSymBuff('a');
                    }
                }else if (player->getDirection() != 'd' && (hl.first != 16 || hl.second != 16)){
                    tmp_sym = (tmp_sym == 'q') ? 'a' : tmp_sym;
                    player->setSymBuff(tmp_sym);
                }
                break;
            case SDLK_SPACE:
                std::this_thread::sleep_for(std::chrono::seconds(10000));
                break;
            default:
                break;
        }
    }
}

void Game_sdl::update() {
    player->Update();
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
