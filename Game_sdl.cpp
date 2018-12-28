#include "Game_sdl.hpp"
//#include "GameObj_sdl.hpp"



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
    //std::cout << dir << std::endl;
    size_t  n = dir.rfind('/');
    dir.resize(n);
    map = std::make_shared<Map>(Map(1440, 1072));//1440 | 1072
    //player = std::make_shared<GameObj_sdl>(GameObj_sdl((dir + "/Picture/dirt.png").c_str(), 200, 16, map->_map,'d'));
    player = new GameObj_sdl( (dir + "/Picture/dirt.png").c_str(), 200, 16, map->_map,'d');
    food = std::make_shared<Food>((dir + "/Picture/small_food.png").c_str(), (dir + "/Picture/big_food.png").c_str());
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
            std::cout << 'w' << std::endl;
                if (player->getDirection() != 's' && (hl.first == 16 && hl.second == 16)){
                    if (tmp_sym == 'q')
                        player->setDirection('w');
                    else if (tmp_sym != 'q'){
                        player->setDirection(tmp_sym);
                        player->setSymBuff('w');
                    }
                } else if (player->getDirection() != 's' && (hl.first != 16 || hl.second != 16)){
                    if (tmp_sym == 'q')
                        player->setSymBuff('w');
                }
                break;
            case SDLK_s://2
            std::cout << 's' << std::endl;
                if (player->getDirection() != 'w' && (hl.first == 16 && hl.second == 16)){
                    if (tmp_sym == 'q')
                        player->setDirection('s');
                    else if (tmp_sym != 'q'){
                        player->setDirection(tmp_sym);
                        player->setSymBuff('s');
                    }
                }else if (player->getDirection() != 'w' && (hl.first != 16 || hl.second != 16)){
                    if (tmp_sym == 'q')
                        player->setSymBuff('s');
                }
                break;
            case SDLK_d://3
            std::cout << 'd' << std::endl;
                if (player->getDirection() != 'a' && (hl.first == 16 && hl.second == 16)){
                    if (tmp_sym == 'q')
                        player->setDirection('d');
                    else if (tmp_sym != 'q'){
                        player->setDirection(tmp_sym);
                        player->setSymBuff('d');
                    }
                }else if (player->getDirection() != 'a' && (hl.first != 16 || hl.second != 16)){
                    if (tmp_sym == 'q')
                        player->setSymBuff('d');
                }
                break;
            case SDLK_a:
                std::cout << 'a' << std::endl;
                if (player->getDirection() != 'd' && (hl.first == 16 && hl.second == 16)){
                    if (tmp_sym == 'q')
                        player->setDirection('a');
                    else if (tmp_sym != 'q'){
                        player->setDirection(tmp_sym);
                        player->setSymBuff('a');
                    }
                }else if (player->getDirection() != 'd' && (hl.first != 16 || hl.second != 16)){
                    if (tmp_sym == 'q')
                        player->setSymBuff('a');
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

    food->mandatoryFood(map->_map);
}

void Game_sdl::render() {
    SDL_RenderClear(renderer);
    map->DrawMap();
    player->Render(map->_map, food);
    if (food->flag == true)
        food->DrawFood();
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
