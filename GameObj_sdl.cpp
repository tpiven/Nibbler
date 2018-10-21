//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#include "GameObj_sdl.hpp"
#include "TextureManager.hpp"
#define MOVE_X (_cors[0].first == _cors[1].first && _cors[0].second != _cors[1].second)
#define MOVE_Y (_cors[0].first != _cors[1].first && _cors[0].second == _cors[1].second)

GameObj_sdl::GameObj_sdl(const char *texture, int y, int x, char direction) : ypos(y), xpos(x) {
    //_objTexture = TextureManager::LoadTexture(texture);
    /*SDL_Surface *tmp_surface = IMG_Load(texture);
    _objTexture = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);*/
    SDL_Surface  *tmp_surface[3];// = IMG_Load(texture);
    _fr_blockX = "NULL";
    _direction = direction;
    _turn = false;
    if (_direction == 'w' || _direction == 's'){
        ypos = (_direction == 'w') ?  -1 : 1;
        xpos = 0;
    }
    else if (_direction == 'a' || _direction == 'd'){
        ypos = 0;
        xpos = (_direction == 'a') ? -1 : 1;
    }
    tmp_surface[0] = IMG_Load(texture);
    tmp_surface[1] = IMG_Load("/Users/kmykhail/Desktop/Nibbler/Picture/grass_bloc_mod.png");
    tmp_surface[2] = IMG_Load("/Users/kmykhail/Desktop/Nibbler/Picture/dirt_1.png");
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
    snakeTexture[2] = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[0]);//head


    _cors[0] = std::make_pair(y, x + 16);//tail
    _cors[1] = std::make_pair(y, x + (16 * 2));
    _cors[2] = std::make_pair(y, x + (16 * 3));//head


    high = low = scrR.h = 16;
    scrR.w = 16;

    SDL_FreeSurface(tmp_surface[0]);
    SDL_FreeSurface(tmp_surface[1]);
    SDL_FreeSurface(tmp_surface[2]);
    //SDL_FreeSurface(&(*tmp_surface));
}

void GameObj_sdl::Update() {

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

bool GameObj_sdl::AreSnakeBlocksEqual() {
    if (_cors[0].first == (--_cors.end())->second.first || _cors[0].second == (--_cors.end())->second.second)
        return true;
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
            scrR.x = (_direction == 's') ? (++_cors[cnt_cors].second) : (--_cors[cnt_cors].second);
            scrR.y = _cors[cnt_cors + 1].first;
            scrR.w = --low;
            scrR.h = 16;
        }
    }
    else if (!low || !high){
        scrR.h = scrR.w = 16;
        _cors[cnt_cors].second = scrR.x = (cnt_cors == _cors.size() - 1) ? _cors[cnt_cors].second : _cors[cnt_cors + 1].second;
        if (cnt_cors == _cors.size() - 1)
            _cors[cnt_cors].first = scrR.y = (_direction == 's') ? _cors[cnt_cors].first + 16 : _cors[cnt_cors].first - 16;
        else
            _cors[cnt_cors].first = scrR.y = _cors[cnt_cors + 1].first;
        (cnt_cors == _cors.size() - 1) ? (low = high = 16) : 0;
        _turn = (cnt_cors == _cors.size() - 1) ? false : _turn;
    }
    else{
        if (cnt_cors == _cors.size() - 1){
            scrR.x = _cors[cnt_cors].second;
            scrR.y = _cors[cnt_cors].first;
            scrR.w = 16;
            scrR.h = (_direction == 's') ?  ++high : --high;
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
            scrR.x = _cors[cnt_cors + 1].second;
            scrR.y = (_direction == 'd') ? (++_cors[cnt_cors].first) : (--_cors[cnt_cors].first);
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
        (cnt_cors == _cors.size() - 1) ? (low = high = 16) : 0;
        _turn = (cnt_cors == _cors.size() - 1) ? false : _turn;
    }
    else{
        if (cnt_cors == _cors.size() - 1){
            scrR.x = _cors[cnt_cors].second;
            scrR.y = _cors[cnt_cors].first;
            scrR.w = (_direction == 'd') ?  ++low : --low;
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
    if (!_turn && !AreSnakeBlocksEqual())
        _turn = true;
    if (!_turn){
        if (cnt_cors == _cors.size() - 1){
            _cors[cnt_cors].second = scrR.x = _cors[cnt_cors].second + xpos;
            _cors[cnt_cors].first = scrR.y = _cors[cnt_cors].first + ypos;
        }else {
            _cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second - 16 + 1;
            _cors[cnt_cors].first = scrR.y = _cors[cnt_cors + 1].first;
        }
    }
    else if (_turn) {
        turnOnY(cnt_cors);
    }
}

void GameObj_sdl::moveOnY(size_t & cnt_cors) {
    _fr_blockX = (!cnt_cors) ? "moveOnY" : _fr_blockX;
    if (!_turn && !AreSnakeBlocksEqual())
        _turn = true;
    if (!_turn){
        if (cnt_cors == _cors.size() - 1){
            _cors[cnt_cors].second = scrR.x = _cors[cnt_cors].second + xpos;
            _cors[cnt_cors].first = scrR.y = _cors[cnt_cors].first + ypos;
        }else {
            _cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second;
            _cors[cnt_cors].first = scrR.y = std::abs(_cors[cnt_cors + 1].first - 16 + 1); //can be trouble with (STD::ABS())
        }
    }
    else if (_turn) {
        turnOnX(cnt_cors);
    }
}

void GameObj_sdl::Render() {
    for (size_t cnt_cors = 0, cnt_s = 0; cnt_s < snakeTexture.size() ; ++cnt_s, ++cnt_cors) {
        if ((cnt_cors == _cors.size() - 1 && _fr_blockX == "moveOnX") || ((cnt_cors != _cors.size() - 1) && (_cors[cnt_cors].first == _cors[cnt_cors + 1].first) && (_cors[cnt_cors].second != _cors[cnt_cors + 1].second)))//идем по оси X
            moveOnX(cnt_cors);
        else if ((cnt_cors == _cors.size() - 1 && _fr_blockX == "moveOnY") || ((cnt_cors != _cors.size() -1) && (_cors[cnt_cors].first !=_cors[cnt_cors + 1].first) &&(_cors[cnt_cors].second == _cors[cnt_cors + 1].second)))//идем по оси Y
            moveOnY(cnt_cors);
        if(_cors[1].first == 217){
            std::cout << "CNT_CORS: " << cnt_cors << "_CORS.SIZE()" << _cors.size() << std::endl;
            std::cout << "!!" << std::endl;
        }
        SDL_RenderCopy(Game_sdl::renderer, snakeTexture[cnt_s], NULL, &scrR);
    }


    std::cout << "CORS[0].first: " << _cors[0].first << " CORS[0].second:" << _cors[0].second << std::endl;
}

void GameObj_sdl::setDirection(char dir) { _direction = dir; }
