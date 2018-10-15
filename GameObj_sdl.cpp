//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#include "GameObj_sdl.hpp"
#include "TextureManager.hpp"

GameObj_sdl::GameObj_sdl(const char *texture, int y, int x, char direction) : ypos(y), xpos(x) {
    //_objTexture = TextureManager::LoadTexture(texture);
    /*SDL_Surface *tmp_surface = IMG_Load(texture);
    _objTexture = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface);
    SDL_FreeSurface(tmp_surface);*/
    SDL_Surface  *tmp_surface[3];// = IMG_Load(texture);
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

void GameObj_sdl::Render() {
    for (size_t cnt_cors = 0, cnt_s = 0; cnt_s < snakeTexture.size() ; ++cnt_s, ++cnt_cors) {
        if (cnt_cors == _cors.size() -1 || ((_cors[cnt_cors].first == _cors[cnt_cors + 1].first)  && (_cors[cnt_cors].second != _cors[cnt_cors + 1].second)))//(y(0)==y(1) && x(0) != x(1) )
        {
            if (!_turn){
                if (cnt_cors == _cors.size() - 1){
                    _cors[cnt_cors].second = scrR.x = _cors[cnt_cors].second + xpos;
                    _cors[cnt_cors].first = scrR.y = _cors[cnt_cors].first + ypos;
                }else {
                    _cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second - 16 + 1;
                    _cors[cnt_cors].first = scrR.y = _cors[cnt_cors + 1].first;
                }
            }
            else if (_turn){
                if (!cnt_cors && low){

                    if (low - 1 == 0){
                       _cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second;
                       _cors[cnt_cors].first = scrR.y = _cors[cnt_cors + 1].first;
                       scrR.h = scrR.w = 16;
                       low = 0;
                    }
                    else{
                        scrR.x = ++_cors[cnt_cors].second;
                        scrR.y = _cors[cnt_cors + 1].first;
                        scrR.w = --low;
                        scrR.h = 16;
                    }
                }
                else if (!low){
                    scrR.h = scrR.w = 16;
                    _cors[cnt_cors].second = scrR.x = (cnt_cors == _cors.size() - 1) ? _cors[cnt_cors].second : _cors[cnt_cors + 1].second;
                    if (cnt_cors == _cors.size() - 1)
                        _cors[cnt_cors].first = scrR.y = (_direction == 's') ? _cors[cnt_cors].first + 16 : _cors[cnt_cors].first - 16;
                    else
                        _cors[cnt_cors].first = scrR.y = _cors[cnt_cors + 1].first;
                    if (cnt_cors == _cors.size() - 1){
                        low = high = 16;
                    }
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
                        scrR.x = _cors[cnt_cors].second;
                        scrR.y = _cors[cnt_cors + 1].first;
                    }
                }
            }
        }
        else if ((_cors[cnt_cors].first !=_cors[cnt_cors + 1].first) &&(_cors[cnt_cors].second == _cors[cnt_cors + 1].second)){
            if (!_turn){
                if (cnt_cors == _cors.size() - 1){
                    _cors[cnt_cors].second = scrR.x = _cors[cnt_cors].second + xpos;
                    _cors[cnt_cors].first = scrR.y = _cors[cnt_cors].first + ypos;
                }else {
                    _cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second;
                    _cors[cnt_cors].first = scrR.y = std::abs(_cors[cnt_cors + 1].first - 16 + 1);
                }
            }
            else if (_turn){
                if (!cnt_cors && high){
                    scrR.x = _cors[cnt_cors + 1].second;
                    scrR.y = ++_cors[cnt_cors].first;
                    scrR.w = 16;
                    scrR.h = --high;
                }
                else if (!high){
                    scrR.w = scrR.h = 16;
                    if (cnt_cors == _cors.size() - 1)
                        _cors[cnt_cors].second = scrR.x = (_direction == 'd') ?_cors[cnt_cors].second + 16 : _cors[cnt_cors].second - 16;
                    else
                        _cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second;
                    //_cors[cnt_cors].second = scrR.x = _cors[cnt_cors + 1].second
                    _cors[cnt_cors].first = scrR.y = (cnt_cors == _cors.size() - 1) ? _cors[cnt_cors].first : _cors[cnt_cors + 1].first;
                    _turn = (cnt_cors == _cors.size() - 1) ? false : _turn;
                    low = high = 16;
                }
                else{
                    if (cnt_cors == _cors.size() - 1){
                        scrR.x = _cors[cnt_cors].second;
                        scrR.y = _cors[cnt_cors].first;
                        scrR.w = (_direction == 'd') ? ++low : --low;
                        scrR.h = 16;
                    }
                    else {
                        scrR.w =scrR.h = 16;
                        scrR.x = _cors[cnt_cors + 1].second;
                        if (low)
                            _cors[cnt_cors].first = scrR.y = _cors[cnt_cors + 1].first;
                        else
                            scrR.y = _cors[cnt_cors].first;
                    }
                }
            }
        }
        SDL_RenderCopy(Game_sdl::renderer, snakeTexture[cnt_s], NULL, &scrR);
    }
    /*for (size_t cnt_arr = _corXY.size() - 1, cnt_s = snakeTexture.size() - 1;  cnt_s != 0 ; cnt_arr -= 2, --cnt_s) {
        if ((_corXY[cnt_arr - 1] == _corXY[cnt_arr - 3]) && (_corXY[cnt_arr] != _corXY[cnt_arr - 2])) {
            if (!_turn) {
                _corXY[cnt_arr] = scrR.x = _corXY[cnt_arr - 2] - 16 + 1;
                _corXY[cnt_arr - 1] = scrR.y = _corXY[cnt_arr - 3];
            }
            else {
                if (low == 1) {
                    scrR.h = 16;
                    scrR.w = 16;
                    _corXY[cnt_arr] = scrR.x = _corXY[cnt_arr - 2];
                    _corXY[cnt_arr - 1] = scrR.y = _corXY[cnt_arr - 3];
                }
                else if (cnt_arr == _corXY.size() - 1) {
                    scrR.x = ++_corXY[cnt_arr];
                    scrR.y = _corXY[cnt_arr - 1];
                    scrR.w = --low;
                    scrR.h = 16;
                }
                else {
                    scrR.x = _corXY[cnt_arr];
                    scrR.y = _corXY[cnt_arr - 1];
                    scrR.h = scrR.w = 16;
                }
            }
        }
        else if ((_corXY[cnt_arr - 1] != _corXY[cnt_arr - 3]) && (_corXY[cnt_arr] == _corXY[cnt_arr - 2])){
            if (!_turn){
                _corXY[cnt_arr] = scrR.x = _corXY[cnt_arr - 2];
                _corXY[cnt_arr - 1] = scrR.y = std::abs(_corXY[cnt_arr - 3] - 16 + 1);
            }
            else{
                _corXY[0] = scrR.y = _corXY[0] + ypos;
                _corXY[1] = scrR.x = _corXY[1] + ((xpos >= 0) ? 16 : -16);
            }
        }
        SDL_RenderCopy(Game_sdl::renderer, snakeTexture[cnt_s], NULL, &scrR);
    }
    if (!_turn){
        _corXY[0] = scrR.y = _corXY[0] + ypos;
        _corXY[1] = scrR.x = _corXY[1] + xpos;
    }
    else if (_turn){
        if (low != 1){
            scrR.x = _corXY[1];
            scrR.y = _corXY[0];
            scrR.h = ++high;
            scrR.w = 16;
        }
        else if (ypos != 0){
            _corXY[0] = scrR.y = _corXY[0] + ((ypos > 0) ? 16 : -16);
            _corXY[1] = scrR.x = _corXY[1] + xpos;
           low = high =  scrR.h = scrR.w = 16;
        }
        else if (xpos != 0){
            _corXY[0] = scrR.y = _corXY[0] + ypos;
            _corXY[1] = scrR.x = _corXY[1] + ((xpos > 0) ? 16 : -16);
            low = high = scrR.h = scrR.w = 16;
        }
    }
    SDL_RenderCopy(Game_sdl::renderer, snakeTexture[0], NULL, &scrR);

    if ((_direction == 'w' ||_direction == 's') && (_corXY[1] == _corXY[_corXY.size() - 1])){
        _turn = false;
        low = 16;
        high = 16;
    }*/
    /*for (size_t cnt_arr = _corXY.size() - 1, cnt_s = snakeTexture.size() - 1;  cnt_s != 0 ; cnt_arr -= 2, --cnt_s) {
        if ((_corXY[cnt_arr - 1] == _corXY[cnt_arr - 3]) && (_corXY[cnt_arr] != _corXY[cnt_arr - 2])){//move on X
            if (!_turn){
                _corXY[cnt_arr] = scrR.x = _corXY[cnt_arr - 2] - 16 + 1;
                _corXY[cnt_arr - 1] = scrR.y = _corXY[cnt_arr - 3];
            }
            else if(_turn){
                if (cnt_arr == _corXY.size() - 1){
                    scrR.x = ++_corXY[cnt_arr];
                    scrR.y = _corXY[cnt_arr - 1];
                    scrR.w = --low;
                    scrR.h = 16;
                }
                else if(!low){
                    scrR.h = scrR.w = 16;
                    _corXY[cnt_arr] = scrR.x = _corXY[cnt_arr - 2];
                    _corXY[cnt_arr - 1] = scrR.y = _corXY[cnt_arr - 3];
                }
                else{
                    scrR.x = _corXY[cnt_arr];
                    scrR.y = _corXY[cnt_arr - 1];
                }
            }
        }
        else if ((_corXY[cnt_arr - 1] != _corXY[cnt_arr - 3]) && (_corXY[cnt_arr] == _corXY[cnt_arr - 2])){ //move on Y
            if (!_turn){
                _corXY[cnt_arr] = scrR.x = _corXY[cnt_arr - 2];
                _corXY[cnt_arr - 1] = scrR.y = std::abs(_corXY[cnt_arr - 3] - 16 + 1);
            }
            else if (_turn){

            }
        }
        SDL_RenderCopy(Game_sdl::renderer, snakeTexture[cnt_s], NULL, &scrR);
    }*/

}

void GameObj_sdl::setDirection(char dir) { _direction = dir; }
