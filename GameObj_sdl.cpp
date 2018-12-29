//
// Created by Kostiantyn MYKHAILENKO on 8/22/18.
//

#include "GameObj_sdl.hpp"
#include "TextureManager.hpp"
#include "glob.hpp"


#define MOVE_X (_cors[0].first == _cors[1].first && _cors[0].second != _cors[1].second)
#define MOVE_Y (_cors[0].first != _cors[1].first && _cors[0].second == _cors[1].second)


GameObj_sdl::GameObj_sdl(const char *texture, int y, int x, int (*toto)[67][90], char direction) : ypos(y), xpos(x) {
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
   // _food = SDL_CreateTextureFromSurface(Game_sdl::renderer, tmp_food);
    for(int i = 0; i < 4; i++)
        (*toto)[(y * 67 / g_height) - 1][(x * 90 / 1440) + i] = -1;
    _cors.insert(std::make_pair(0,  std::make_pair(y, x + 16)));
    _cors.insert(std::make_pair(1,  std::make_pair(y, x + (16*2))));
    _cors.insert(std::make_pair(2,  std::make_pair(y, x + (16*3))));
    _cors.insert(std::make_pair(3,  std::make_pair(y, x + (16*4))));


//    _cors[0] = std::make_pair(y, x + 16);//tail
//    _cors[1] = std::make_pair(y, x + (16 * 2));
//    _cors[2] = std::make_pair(y, x + (16 * 3));
//    _cors[3] = std::make_pair(y, x + (16 * 4));//head

    high = low = scrR.h = 16;
    scrR.w = 16;

    SDL_FreeSurface(tmp_surface[0]);
    SDL_FreeSurface(tmp_surface[1]);
    SDL_FreeSurface(tmp_surface[2]);
    //SDL_FreeSurface(&(*tmp_surface));
}

void GameObj_sdl::Update() {
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
  //  std::cout << "CNT_CORS!!!!!!!!!!!!!! " << cnt_cors << std:: endl;
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

void GameObj_sdl::Render(int (*&m_map)[67][90], std::shared_ptr<Food> & food) {
    std::pair<int, int> prev_cor[2], pres_cor[2];
    _cnt_block = _cors.size() - 1;
   // std::cout << " BLOKS    " << _cnt_block << std::endl;
    for (size_t cnt_cors = 0, cnt_s = 0; cnt_cors < _cors.size() ; ++cnt_s, ++cnt_cors) {

        //TODO prev_cor it's pair <y,x> on double array before move
//        get_cor(cnt_cors);
//        prev_cor[0] = _head_dots[0];
//        prev_cor[1] = _head_dots[1];



        if ((cnt_cors == _cors.size() - 1 && _fr_blockX == "moveOnX") || ((cnt_cors != _cors.size() - 1) && (_cors[cnt_cors].first == _cors[cnt_cors + 1].first) && (_cors[cnt_cors].second != _cors[cnt_cors + 1].second)))//идем по оси X
            moveOnX(cnt_cors);
        else if ((cnt_cors == _cors.size() - 1 && _fr_blockX == "moveOnY") || ((cnt_cors != _cors.size() -1) && (_cors[cnt_cors].first !=_cors[cnt_cors + 1].first) &&(_cors[cnt_cors].second == _cors[cnt_cors + 1].second)))//идем по оси Y
            moveOnY(cnt_cors);


        //TODO pres_cor it's pair <y,x> on double array afters move
        get_cor(cnt_cors);
        pres_cor[0] = std::make_pair(((_head_dots[0].first * 67) / g_height), ((_head_dots[0].second * 90) / g_weight));
        pres_cor[1] = std::make_pair(((_head_dots[1].first * 67) / g_height), ((_head_dots[1].second * 90) / g_weight));
        if (cnt_cors == _cors.size() -1 ) {
            std::cout << "########" << std::endl;
            std::cout << "pres_cor_y: " << pres_cor[0].first << " pres_cor_x: " << pres_cor[0].second << std::endl;
            std::cout << "head_y: " << _head_dots[0].first << "head_x: " << _head_dots[0].second << std::endl;
            std::cout << "head_y: " << _head_dots[1].first << "head_x: " << _head_dots[1].second << std::endl;
            std::cout << "current_y: " << _cors[cnt_cors].first << "current_x: " << _cors[cnt_cors].second << std::endl;
        }
        if (_head_dots[0].first == 208){
            std::cout << "THIS:pres_cor_y: " << pres_cor[0].first << " pres_cor_x: " << pres_cor[0].second << std:: endl;
        }
        if (cnt_cors == _cors.size() - 1 && _cors[cnt_cors].first == 192){
            std::cout << "not ok" <<  std::endl;
            int a = 10;
        }
        //TODO new if ()
        //if (prev_cor != pres_cor && (!cnt_cors ||

            if ((cnt_cors == _cors.size() - 1) && (cnt_cors && (((*m_map)[pres_cor[0].first][pres_cor[0].second] == -2) || (*m_map)[pres_cor[1].first][pres_cor[1].second] == -2))){
                if (_head_dots[0].first == 221){
                    std::cout << "11111" << std::endl;
                }
                std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!" << std::endl;
                std::cout << "map_snake_y: " <<  pres_cor[0].first << " map_snake_x:" << pres_cor[0].second << std::endl;
                std::cout << "cors_snake_y: " << _cors[cnt_cors].first << " cors_snake_x: " << _cors[cnt_cors].second + 16 << std::endl;
                std::cout << "cors_snake_y: " << _head_dots[0].first << " cors_snake_x: " << _head_dots[0].second << std::endl;
                std::cout << "cors_snake_y2: " << _head_dots[1].first << " cors_snake_x2: " << _head_dots[1].second << std::endl;
                std::cout << "food_head_y: " << food->getCorsLilFood().first << " food_head_x: " << food->getCorsLilFood().second << std::endl;
                grow(m_map, food, cnt_cors);
                if (_cors.size() - cnt_cors != 1){
                    cnt_cors++;
                }
            }
          //  else
            //    (!cnt_cors) ? ((*m_map)[prev_cor.first][prev_cor.second] = 0) : ((*m_map)[pres_cor.first][pres_cor.second] = -1);
         SDL_RenderCopy(Game_sdl::renderer, snakeTexture[cnt_s], NULL, &scrR);
    }
}

void GameObj_sdl::get_cor(size_t cnt_cors) {

    if (_direction == 'd') {
        _head_dots[0] = std::make_pair(_cors[cnt_cors].first, (_cors[cnt_cors].second + 16));
        _head_dots[1] = std::make_pair((_cors[cnt_cors].first + 16), (_cors[cnt_cors].second + 16));
    }
    else if (_direction == 'a') {
        _head_dots[0] = std::make_pair(_cors[cnt_cors].first, _cors[cnt_cors].second);
        _head_dots[1] = std::make_pair((_cors[cnt_cors].first + 16), _cors[cnt_cors].second);

    }
    else if (_direction == 'w') {
        _head_dots[0] = std::make_pair(_cors[cnt_cors].first , _cors[cnt_cors].second);
        _head_dots[1] = std::make_pair(_cors[cnt_cors].first, (_cors[cnt_cors].second + 16));

    }
    else if (_direction == 's') {
        _head_dots[0] = std::make_pair((_cors[cnt_cors].first  + 16), _cors[cnt_cors].second);
        _head_dots[1] = std::make_pair((_cors[cnt_cors].first + 16) , (_cors[cnt_cors].second + 16));

    }

}

bool GameObj_sdl::touch(int x, int y, int z, int w, int a, int b) {

    int k, c;

    if (z == x) {
        return (a == x && b > std::min(y, w) && b < std::max(y, w));
    }

    k = (w - y) / (z - x);
    c = y - k * x;

    return b == a * k + c;
}


void GameObj_sdl::grow(int (*m_map)[67][90], std::shared_ptr<Food> & food, size_t cnt_cors) {
    if (touch(_head_dots[0].second, _head_dots[0].first, _head_dots[1].second, _head_dots[1].first, food->getCorsLilFood().second, food->getCorsLilFood().first)\
        || touch(_head_dots[0].second, _head_dots[0].first, _head_dots[1].second, _head_dots[1].first, food->getCorsLilFood().second, food->getCorsLilFood().first + 8)\
        || touch(_head_dots[0].second, _head_dots[0].first, _head_dots[1].second, _head_dots[1].first, food->getCorsLilFood().second + 8, food->getCorsLilFood().first)\
        || touch(_head_dots[0].second, _head_dots[0].first, _head_dots[1].second, _head_dots[1].first, food->getCorsLilFood().second + 8, food->getCorsLilFood().first + 8))  {
        food->flag = false;
        std::cout << "!!!!!!!!!!!!!!!!!!!!!!!!!!grow" << std::endl;
        if (_direction == 'd') {

           _cors.insert(std::make_pair(4,  std::make_pair(0, 0)));
           _cors[4].first = _cors[3].first;
           _cors[4].second = _cors[3].second;
           _cors[3].first = _cors[2].first;
           _cors[3].second = _cors[2].second;
            _cors[2].first = _cors[1].first;
            _cors[2].second = _cors[1].second;
            _cors[1].first = _cors[0].first;
            _cors[1].second = _cors[0].second;
           _cors[0].first = _cors[1].first;
           _cors[0].second = _cors[1].second - 16;
            (*m_map)[(_cors[0].first * 67 / g_height) - 1][(_cors[0].second * 90 / 1440)] = -1;
            snakeTexture[4] = snakeTexture[3];
            snakeTexture[3] = snakeTexture[2];
            (*m_map)[food->getCorsLilFood().first * 67 / g_height][food->getCorsLilFood().second * 90 / g_weight] = 0;
            //std::rotate(_cors.begin(), _cors.rbegin() + 1, _cors.rend());
           // std::rotate(v.rbegin(), v.rbegin() + 1, v.rend());
        }
        else if (_direction == 'a') {
            _cors.insert(std::make_pair(_cors.size(),  std::make_pair(0, 0)));
            _cors[4].first = _cors[3].first;
            _cors[4].second = _cors[3].second;
            _cors[3].first = _cors[2].first;
            _cors[3].second = _cors[2].second;
            _cors[2].first = _cors[1].first;
            _cors[2].second = _cors[1].second;
            _cors[1].first = _cors[0].first;
            _cors[1].second = _cors[0].second;
            _cors[0].first = _cors[1].first;
            _cors[0].second = _cors[1].second + 16;
            (*m_map)[(_cors[0].first * 67 / g_height) - 1][(_cors[0].second * 90 / 1440)] = -1;
            snakeTexture[4] = snakeTexture[3];
            (*m_map)[food->getCorsLilFood().first * 67 / g_height][food->getCorsLilFood().second * 90 / g_weight] = 0;


        }
        else if (_direction == 'w') {
            _cors.insert(std::make_pair(4,  std::make_pair(0, 0)));
            _cors[4].first = _cors[3].first;
            _cors[4].second = _cors[3].second;
            _cors[3].first = _cors[2].first;
            _cors[3].second = _cors[2].second;
            _cors[2].first = _cors[1].first;
            _cors[2].second = _cors[1].second;
            _cors[1].first = _cors[0].first;
            _cors[1].second = _cors[0].second;
            _cors[0].first = _cors[1].first + 16;
            _cors[0].second = _cors[1].second;
            (*m_map)[(_cors[0].first * 67 / g_height) - 1][(_cors[0].second * 90 / 1440)] = -1;
            snakeTexture[4] = snakeTexture[3];
            (*m_map)[food->getCorsLilFood().first * 67 / g_height][food->getCorsLilFood().second * 90 / g_weight] = 0;



        }
        else if (_direction == 's') {
            _cors.insert(std::make_pair(4,  std::make_pair(0, 0)));
            _cors[4].first = _cors[3].first;
            _cors[4].second = _cors[3].second;
            _cors[3].first = _cors[2].first;
            _cors[3].second = _cors[2].second;
            _cors[2].first = _cors[1].first;
            _cors[2].second = _cors[1].second;
            _cors[1].first = _cors[0].first;
            _cors[1].second = _cors[0].second;
            _cors[0].first = _cors[1].first - 16;
            _cors[0].second = _cors[1].second;
            (*m_map)[(_cors[0].first * 67 / g_height) - 1][(_cors[0].second * 90 / 1440)] = -1;
            snakeTexture[4] = snakeTexture[3];
            (*m_map)[food->getCorsLilFood().first * 67 / g_height][food->getCorsLilFood().second * 90 / g_weight] = 0;
        }
    }
}


void GameObj_sdl::setDirection(char dir) { _direction = dir; }

char GameObj_sdl::getDirection() const { return _direction;}

char GameObj_sdl::getSymBuff() const { return _sybBuff;}
void GameObj_sdl::setSymBuff(char sym) { _sybBuff = sym; }


std::pair<int, int > GameObj_sdl::getHighLow() const {
    return std::make_pair(high, low);
}

