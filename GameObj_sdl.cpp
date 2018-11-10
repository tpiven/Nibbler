//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#include "GameObj_sdl.hpp"
#include "TextureManager.hpp"
#include "glob.hpp"

int g_weight;
int g_height;

#define MOVE_X (_cors[0].first == _cors[1].first && _cors[0].second != _cors[1].second)
#define MOVE_Y (_cors[0].first != _cors[1].first && _cors[0].second == _cors[1].second)


GameObj_sdl::GameObj_sdl(const char *texture, int y, int x, char direction) : ypos(y), xpos(x) {
    //_objTexture = TextureManager::LoadTexture(texture);
    /*SDL_Surface *tmp_surface = IMG_Load(texture);
    _objTexture = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);*/
    //g_weight = 123;
//    std::cout << "!!!!!!!!!!!!!" <<  g_weight << std::endl;
    SDL_Surface  *tmp_surface[3];// = IMG_Load(texture);
    _fr_blockX = "NULL";
    _direction = direction;
    _sybBuff = 'q';
    _turn = false;
    buffVal_y = -1;
    buffVal_x = -1;
    _cnt_block = 4;
    if (_direction == 'w' || _direction == 's'){
        ypos = (_direction == 'w') ?  -1 : 1;
        xpos = 0;
    }
    else if (_direction == 'a' || _direction == 'd'){
        ypos = 0;
        xpos = (_direction == 'a') ? -1 : 1;
    }
    //std::cout << "QW: " << g_weight  << " " << g_height << std::endl;
    //exit(0);
    std::cout << "Textura: "  << texture << std::endl;
    tmp_surface[0] = IMG_Load(texture);
    char path[4096];
    std::string dir = getwd(path);//get_current_dir_name();
    size_t  n = dir.rfind('/');
    dir.resize(n);
    tmp_surface[1] = IMG_Load((dir + "/Picture/grass_bloc_mod.png").c_str());
    tmp_surface[2] = IMG_Load((dir + "/Picture/dirt_1.png").c_str());
    scrR_food = nullptr;
    //std::cout << lvl1[0] << std::endl;
    //snakeTexture.push_back(SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[0]));//head

    //_corXY.push_back(y + 0);
    //_corXY.push_back(x + (16 * 4));
    //snakeTexture.push_back(SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[0]));//
    //_cors[1] = std::make_pair(y, x + (16 * 3));
    //_corXY.push_back(y + 0);
    //_corXY.push_back(x + (16 * 3));
    //snakeTexture.push_back(SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[0]));//
    //_cors[2] = std::make_pair(y, x + (16 * 2));
    //_corXY.push_back(y + 0);
    //_corXY.push_back(x + (16 * 2));
    //snakeTexture.push_back(SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[1]));//body
    //_cors[3] = std::make_pair(y , x + 16);
    //_corXY.push_back(y + 0);//middle_y//body_y
    //_corXY.push_back(x + 16);//middle_x//body_x
    //snakeTexture.push_back(SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[2]));
    //_cors[4] = std::make_pair(y, x);
    //_corXY.push_back(y);//last_x//tail_y
    //_corXY.push_back(x);//last_y//tail_x
    snakeTexture[0] = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[2]);//tail
    snakeTexture[1] = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[1]);//body
    snakeTexture[2] = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[1]);
    snakeTexture[3] = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[0]);//head

    SDL_Surface *tmp_food = IMG_Load((dir + "/Picture/block_left_gray.png").c_str());;
    _food = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_food);
//    for(int i = 0; i < 4; i++)
//        map[y][x +(16 * (i + 1))] = -1;
    _cors[0] = std::make_pair(y, x + 16);//tail
    _cors[1] = std::make_pair(y, x + (16 * 2));
    _cors[2] = std::make_pair(y, x + (16 * 3));
    _cors[3] = std::make_pair(y, x + (16 * 4));//head

    high = low = scrR.h = 16;
    scrR.w = 16;

    SDL_FreeSurface(tmp_surface[0]);
    SDL_FreeSurface(tmp_surface[1]);
    SDL_FreeSurface(tmp_surface[2]);
    //SDL_FreeSurface(&(*tmp_surface));
}

void GameObj_sdl::Update() {

    std::cout << "[[[QW: }}}}r" << g_weight  << " " << g_height << std::endl;
    /*if ((_direction == 'w' || _direction == 's') && ((_corXY[0] == _corXY[2]) && (_corXY[1] != _corXY[3]))){
        ypos = (_direction == 'w') ?  -1 : 1;
        xpos = 0;
        _turn = true;
    }
    else if ((_direction == 'a' || _direction == 'd') && ((_corXY[0] != _corXY[2]) && (_corXY[1] == _corXY[3]))){
        ypos = 0;
        xpos = (_direction == 'a') ? -1 : 1;
        _turn = true;
    }*/
    size_t back = _cors.size() - 1;
    if ((_direction == 'w' || _direction == 's') && ((_cors[back].first == _cors[back - 1].first) && (_cors[back].second != _cors[back-1].second))){
        ypos = (_direction == 'w') ? -1 : 1;
        xpos = 0;
        _turn = true;
    }
    else if ((_direction == 'a' || _direction == 'd') && ((_cors[back].first != _cors[back- 1].first) && (_cors[back].second == _cors[back - 1].second))){
        ypos = 0;
        xpos = (_direction == 'a') ? -1 : 1;
        _turn = true;
    }
}

//first == y
//second == x

bool GameObj_sdl::AreSnakeBlocksEqual(int cnt_cors) {
    /*if (_cors[0].first == (--_cors.end())->second.first){
        std::cout << "second: " << _cors[_cnt_block].second - (16 * _cnt_block) << std::endl;
        if (_cors[0].second == _cors[_cnt_block].second - (16 * _cnt_block))
            return std::make_pair(true, std::make_pair('y', (--_cors.end())->second.second - _cors[0].second));
        else
            return std::make_pair(false, std::make_pair('q', 0));
    }
    else if (_cors[0].second == (--_cors.end())->second.second){
        std::cout << "first: " << _cors[_cnt_block].first - (16 * _cnt_block) << std::endl;
        if (_cors[0].first == (_cors[_cnt_block].first - (16 * _cnt_block)))
            return std::make_pair(true, std::make_pair('x', (--_cors.end())->second.first - _cors[0].first));
        else
            return std::make_pair(false, std::make_pair('q', 0));
    }
    else
        return std::make_pair(false, std::make_pair('q', 0));*/
//    if (!cnt_cors && _cors[0].first == (--_cors.end())->second.first && _cors[0].second == _cors[_cnt_block].second - (16 * _cnt_block))
//        return true;
//    else if (!cnt_cors && _cors[0].second == (--_cors.end())->second.second && _cors[0].first == (_cors[_cnt_block].first - (16 * _cnt_block)))
//        return true;
    int min_second  = (_cors[_cnt_block].second < _cors[0].second) ? _cors[_cnt_block].second : _cors[0].second;
    int max_second = (_cors[_cnt_block].second > _cors[0].second) ? _cors[_cnt_block].second : _cors[0].second;

    int min_first = (_cors[_cnt_block].first < _cors[0].first) ? _cors[_cnt_block].first : _cors[0].first;
    int max_first = (_cors[_cnt_block].first > _cors[0].first) ? _cors[_cnt_block].first : _cors[0].first;

    if (!cnt_cors && _cors[0].first == (--_cors.end())->second.first && min_second == max_second - (16 * _cnt_block))
        return  true;
    else if (!cnt_cors && _cors[0].second == (--_cors.end())->second.second && min_first == max_first- (16 * _cnt_block))
        return true;
    else if (cnt_cors)
        return true;
    else
        return false;
}

void GameObj_sdl::turnOnY(size_t &cnt_cors) {
    if (!cnt_cors && low){
        if (low - 1 == 0){
            _cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second;
            _cors[cnt_cors].first = scrR.y = _cors[cnt_cors + 1].first;
            scrR.w = scrR.h = 16;
            low = 0;
        }
        else{
            /*if (_cors[cnt_cors].second < (--_cors.end())->second.second)
                scrR.x = ++_cors[cnt_cors].second;
            else
                scrR.x = --_cors[cnt_cors].second;*/
            if (_cors[cnt_cors].second < _cors[cnt_cors + 1].second)
                scrR.x = ++_cors[cnt_cors].second;
            else
                scrR.x = --_cors[cnt_cors].second;
            scrR.y = _cors[cnt_cors + 1].first;
            scrR.w = --low;
            scrR.h = 16;
        }
    }
    else if (!low || !high){
        scrR.h = scrR.w = 16;
        _cors[cnt_cors].second = scrR.x = (cnt_cors == _cors.size() - 1) ? _cors[cnt_cors].second : _cors[cnt_cors + 1].second;
        if (cnt_cors == _cors.size() - 1) {
            _cors[cnt_cors].first = scrR.y = (_direction == 's') ? _cors[cnt_cors].first + 16 : _cors[cnt_cors].first - 16;
            buffVal_y = _cors[cnt_cors].first;
        }else{
            _cors[cnt_cors].first = scrR.y = _cors[cnt_cors + 1].first;}
        //(cnt_cors == _cors.size() - 1) ? (low = high = 16) : 0;
        //_turn = (cnt_cors == _cors.size() - 1) ? false : _turn;
        if (cnt_cors == _cors.size() - 1){
            low = high = 16;
            _turn = false;
            buffVal_y = -1;
            if (_sybBuff != 'q'){
                _direction = _sybBuff;
                _sybBuff = 'q';
            }
        }
    }
    else{
        if (cnt_cors == _cors.size() - 1){
            scrR.x = _cors[cnt_cors].second;
            buffVal_y = (buffVal_y < 0) ?_cors[cnt_cors].first : buffVal_y;
            //if (_cors[0].first <= (--_cors.end())->second.first){
                //scrR.y = (_direction == 's') ? _cors[cnt_cors].first : --_cors[cnt_cors].first;
            if (_direction == 's')
                buffVal_y = scrR.y = _cors[cnt_cors].first;
            else {
                //scrR.y = _cors[cnt_cors].first;
                scrR.y = --buffVal_y;
            }
                //}
            //else {
                //scrR.y = --_cors[cnt_cors].first;
               // std::cout << "4to to" << std::endl;
           //}
            scrR.w = 16;
            //scrR.h = (_direction == 's') ?  ++high : --high;
            //scrR.h = ++high;
            scrR.h = (high < 16) ? ((16 - high) + 16) : (++high);
        }
        else {
            scrR.w = scrR.h = 16;
            if (_cors[cnt_cors].first == _cors[cnt_cors + 1].first && _cors[cnt_cors].second != _cors[cnt_cors + 1].second) {
                scrR.x = _cors[cnt_cors].second;
                scrR.y = _cors[cnt_cors + 1].first;
            }
            else if (_cors[cnt_cors].first != _cors[cnt_cors + 1].first && _cors[cnt_cors].second == _cors[cnt_cors + 1].second){
                scrR.x = _cors[cnt_cors + 1].second;
                scrR.y = _cors[cnt_cors].first;
            }
        }
    }
}

void GameObj_sdl::turnOnX(size_t &cnt_cors) {
    if (!cnt_cors && high) {
        if (high - 1 == 0){
            _cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second;
            _cors[cnt_cors].first = scrR.y = _cors[cnt_cors + 1].first;
            scrR.w = scrR.h = 16;
            high = 0;
        }
        else{
            /*if (_cors[cnt_cors].first < (--_cors.end())->second.first)
                scrR.y = ++_cors[cnt_cors].first;
            else
                scrR.y = --_cors[cnt_cors].first;*/
            if (_cors[cnt_cors].first < _cors[cnt_cors + 1].first)
                scrR.y = ++_cors[cnt_cors].first;
            else
                scrR.y = --_cors[cnt_cors].first;
            scrR.x = _cors[cnt_cors + 1].second;
            scrR.w = 16;
            scrR.h = --high;
        }
    }
    else if (!high || !low) {
        scrR.w = scrR.h = 16;
        _cors[cnt_cors].first = scrR.y = (cnt_cors == _cors.size() - 1) ? _cors[cnt_cors].first : _cors[cnt_cors + 1].first;
        if (cnt_cors == _cors.size() - 1)
            _cors[cnt_cors].second = scrR.x = (_direction == 'd') ? _cors[cnt_cors].second + 16 : _cors[cnt_cors].second - 16;
        else
            _cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second;
        //(cnt_cors == _cors.size() - 1) ? (low = high = 16) : 0;
        //_turn = (cnt_cors == _cors.size() - 1) ? false : _turn;
        if (cnt_cors == _cors.size() - 1){
            low = high = 16;
            _turn = false;
            buffVal_x = -1;
            if (_sybBuff != 'q') {
                _direction = _sybBuff;
                _sybBuff = 'q';
            }
        }
    }
    else{
        if (cnt_cors == _cors.size() - 1){
            //scrR.x = _cors[cnt_cors].second;
            scrR.y = _cors[cnt_cors].first;
            //scrR.w = (_direction == 'd') ?  ++low : --low;
            buffVal_x = (buffVal_x < 0) ? _cors[cnt_cors].second : buffVal_x;
            if (_direction == 'd')
                buffVal_x = scrR.x = _cors[cnt_cors].second;
            else
                scrR.x = --buffVal_x;
            //scrR.w = ++low;
            //if (low < 16)
            scrR.w = (low < 16) ? ((16 - low) + 16) : (++low);
            scrR.h = 16;
        }
        else{
            scrR.w = scrR.h = 16;
            if (_cors[cnt_cors].first != _cors[cnt_cors + 1].first && _cors[cnt_cors].second == _cors[cnt_cors + 1].second) {
                scrR.x = _cors[cnt_cors + 1].second;
                scrR.y = _cors[cnt_cors].first;
            }
            else if (_cors[cnt_cors].first == _cors[cnt_cors + 1].first && _cors[cnt_cors].second != _cors[cnt_cors + 1].second){
                scrR.x = _cors[cnt_cors].second;
                scrR.y = _cors[cnt_cors + 1].first;
            }
        }
    }
}

void GameObj_sdl::moveOnX(size_t &cnt_cors) {
    _fr_blockX = (!cnt_cors) ? "moveOnX" : _fr_blockX;
    if (!_turn && !AreSnakeBlocksEqual(cnt_cors))
        _turn = true;
    if (!_turn){
        if (cnt_cors == _cors.size() - 1){
            _cors[cnt_cors].second = scrR.x = _cors[cnt_cors].second + xpos;
            _cors[cnt_cors].first = scrR.y = _cors[cnt_cors].first + ypos;
        }else {
            _cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second - ((_direction == 'd') ? 15 : -15);
            _cors[cnt_cors].first = scrR.y = _cors[cnt_cors + 1].first;
        }
    }
    else if (_turn) {
        if (cnt_cors == _cors.size() - 1 && (_direction == 'a' || _direction == 'd'))
            turnOnX(cnt_cors);
        else
            turnOnY(cnt_cors);
    }
}

void GameObj_sdl::moveOnY(size_t & cnt_cors) {
    _fr_blockX = (!cnt_cors) ? "moveOnY" : _fr_blockX;
    if (!_turn && !AreSnakeBlocksEqual(cnt_cors))
        _turn = true;
    if (!_turn){
        if (cnt_cors == _cors.size() - 1){
            _cors[cnt_cors].second = scrR.x = _cors[cnt_cors].second + xpos;
            _cors[cnt_cors].first = scrR.y = _cors[cnt_cors].first + ypos;
        }else {
            _cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second;
            _cors[cnt_cors].first = scrR.y = std::abs(_cors[cnt_cors + 1].first -  ((_direction == 's') ? 15 : -15)); //can be trouble with (STD::ABS())
        }
    }
    else if (_turn) {
        if (cnt_cors == _cors.size() - 1 && (_direction == 's' || _direction == 'w'))
            turnOnY(cnt_cors);
        else
            turnOnX(cnt_cors);
    }
}

void GameObj_sdl::Render() {
    _cnt_block = _cors.size() - 1;
    for (size_t cnt_cors = 0, cnt_s = 0; cnt_s < snakeTexture.size() ; ++cnt_s, ++cnt_cors) {
        if ((cnt_cors == _cors.size() - 1 && _fr_blockX == "moveOnX") || ((cnt_cors != _cors.size() - 1) && (_cors[cnt_cors].first == _cors[cnt_cors + 1].first) && (_cors[cnt_cors].second != _cors[cnt_cors + 1].second)))//идем по оси X
            moveOnX(cnt_cors);
        else if ((cnt_cors == _cors.size() - 1 && _fr_blockX == "moveOnY") || ((cnt_cors != _cors.size() -1) && (_cors[cnt_cors].first !=_cors[cnt_cors + 1].first) &&(_cors[cnt_cors].second == _cors[cnt_cors + 1].second)))//идем по оси Y
            moveOnY(cnt_cors);
        SDL_RenderCopy(Game_sdl::renderer, snakeTexture[cnt_s], NULL, &scrR);
    }
    //std::cout << "High: " << high << " Low: " << low << std::endl;
}

void GameObj_sdl::grow() {
    //_cors.emplace(_cnt_block, );
}

void GameObj_sdl::mandatoryFood() {
    /*if (!scrR_food) {
        scrR_food = new SDL_Rect;
        srand(time(NULL));
        while (scrR_food->x <= 0)
            g_weight = rand() % g_weight;
        while(scrR_food->y <= 0)
            g_height = rand() % g_height;
        scrR_food->h = 8;
        scrR_food->w = 8;
    }*/
    //SDL_RenderCopy(Game_sdl);
}

void GameObj_sdl::setDirection(char dir) { _direction = dir; }

char GameObj_sdl::getDirection() const { return _direction;}

char GameObj_sdl::getSymBuff() const { return _sybBuff;}
void GameObj_sdl::setSymBuff(char sym) { _sybBuff = sym; }

//bool GameObj_sdl::canMoveX() const {
//    if
//}

std::pair<int, int > GameObj_sdl::getHighLow() const {
    return std::make_pair(high, low);
}

