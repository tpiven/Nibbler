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
    _turn = true;
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
    snakeTexture.push_back(SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[0]));//head
    _corXY.push_back(y + 0);
    _corXY.push_back(x + (16 * 4));
    snakeTexture.push_back(SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[0]));//
    _corXY.push_back(y + 0);
    _corXY.push_back(x + (16 * 3));
    snakeTexture.push_back(SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[0]));//
    _corXY.push_back(y + 0);
    _corXY.push_back(x + (16 * 2));
    snakeTexture.push_back(SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[1]));//body
    _corXY.push_back(y + 0);//middle_y//body_y
    _corXY.push_back(x + 16);//middle_x//body_x
    snakeTexture.push_back(SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_surface[2]));//tail
    _corXY.push_back(y);//last_x//tail_y
    _corXY.push_back(x);//last_y//tail_x

    scrR.h = 16;
    scrR.w = 16;

    SDL_FreeSurface(tmp_surface[0]);
    SDL_FreeSurface(tmp_surface[1]);
    SDL_FreeSurface(tmp_surface[2]);
    //SDL_FreeSurface(&(*tmp_surface));
}

void GameObj_sdl::Update() {

    if ((_direction == 'w' || _direction == 's') && ((_corXY[0] == _corXY[2]) && (_corXY[1] != _corXY[3]))){
        ypos = (_direction == 'w') ?  -1 : 1;
        xpos = 0;
        _turn = true;
    }
    else if ((_direction == 'a' || _direction == 'd') && ((_corXY[0] != _corXY[2]) && (_corXY[1] == _corXY[3]))){
        ypos = 0;
        xpos = (_direction == 'a') ? -1 : 1;
        _turn = true;
    }
}

void GameObj_sdl::Render() {
    for (size_t cnt_arr = _corXY.size() - 1, cnt_s = snakeTexture.size() - 1;  cnt_s != 0 ; cnt_arr -= 2, --cnt_s) {
        /*_corXY[cnt_arr] = scrR.x = _corXY[cnt_arr - 2] - 16 + xpos;//не меняеться ypos
        if (_corXY[cnt_arr - 1] != _corXY[cnt_arr - 3])
            _corXY[cnt_arr - 1] = scrR.y = _corXY[cnt_arr - 3] - 16 + ypos;
        else
            _corXY[cnt_arr - 1] = scrR.y = _corXY[cnt_arr - 3];*/
        if ((_corXY[cnt_arr - 1] == _corXY[cnt_arr - 3]) && (_corXY[cnt_arr] != _corXY[cnt_arr - 2])) {
            if (!_turn) {
                _corXY[cnt_arr] = scrR.x = _corXY[cnt_arr - 2] - 16 + 1;
                _corXY[cnt_arr - 1] = scrR.y = _corXY[cnt_arr - 3];
            }
            else{
                _corXY[cnt_arr] = scrR.x = _corXY[cnt_arr - 2];
                _corXY[cnt_arr - 1] = scrR.y = _corXY[cnt_arr - 3];
            }
        }
        else if ((_corXY[cnt_arr - 1] != _corXY[cnt_arr - 3]) && (_corXY[cnt_arr] == _corXY[cnt_arr - 2])){
            if (!_turn) {
                _corXY[cnt_arr] = scrR.x = _corXY[cnt_arr - 2];
                _corXY[cnt_arr - 1] = scrR.y = _corXY[cnt_arr - 3] - 16 + 1;
            }
            else{
                _corXY[cnt_arr] = scrR.x = _corXY[cnt_arr - 2];
                _corXY[cnt_arr - 1] = scrR.y = _corXY[cnt_arr - 3];
            }
        }
        SDL_RenderCopy(Game_sdl::renderer, snakeTexture[cnt_s], NULL, &scrR);
    }
    if (_turn){
        if (ypos != 0){
            _corXY[0] = scrR.y = _corXY[0] + ((ypos > 0) ? 16 : -16);
            _corXY[1] = scrR.x = _corXY[1] + xpos;
        }
        else if (xpos != 0){
            _corXY[0] = scrR.y = _corXY[0] + ypos;
            _corXY[1] = scrR.x = _corXY[1] + ((xpos > 0) ? 16 : -16);
        }
    }
    else {
        _corXY[0] = scrR.y = _corXY[0] + ypos;
        _corXY[1] = scrR.x = _corXY[1] + xpos;
    }
    SDL_RenderCopy(Game_sdl::renderer, snakeTexture[0], NULL, &scrR);
    if ((_corXY[0] == _corXY[_corXY.size() - 2]) || _corXY[1] == _corXY[_corXY.size() - 1]){
        _turn = false;
    }
}

void GameObj_sdl::setDirection(char dir) { _direction = dir; }