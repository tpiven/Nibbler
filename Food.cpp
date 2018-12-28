#include "Food.hpp"
#include "glob.hpp"
int g_weight;
int g_height;


Food::Food(const char *lil_food, const char *big_food){
    _texture_food_lil = TextureManager::LoadTexture(big_food);
    _texture_food_big = TextureManager::LoadTexture(big_food);
    _cor_lil_food = std::make_pair(-1, -1);
    _cor_big_food = std::make_pair(-1, -1);
    _move_food_x = _move_food_y = 0;
    flag = true;
}

void Food::mandatoryFood(int (*m_map)[67][90]){

    static int cnt = 0;
    if (flag == true) {
        if (_cor_lil_food.first == -1 || _cor_lil_food.second == -1) {
            int x_map = -1, y_map = -1;
            srand(time(NULL));
            while (y_map == -1 || x_map == -1) {
                y_map = (200 * 67 / 1072) + 1 ;
                //_map = rand() % 67;
                x_map = 30;
               // x_map = rand() % 90;
                if ((*m_map)[y_map][x_map] != 0) {
                    y_map = x_map = -1;
                } else {
                    scrR_lil.y = _cor_lil_food.first = ((y_map * g_height)) / 67;
                    scrR_lil.x = _cor_lil_food.second = ((x_map * g_weight)) / 90;
                    (*m_map)[y_map][x_map] = -2; //-2 food
                }
            }
       }
// else {
//            if ((_move_food_y < 8 && _move_food_x < 8) && cnt == 7) {
//                _move_food_x++;
//                scrR_lil.x = _cor_lil_food.second++;
//            } else if ((_move_food_y < 8 && _move_food_x > 0) && cnt == 7) {
//                _move_food_y++;
//                _move_food_x--;
//                scrR_lil.y = _cor_lil_food.first++;
//                scrR_lil.x = _cor_lil_food.second--;
//            } else if ((_move_food_y > 0 && _move_food_x < 8) && cnt == 7) {
//                _move_food_x++;
//                scrR_lil.x = _cor_lil_food.second++;
//            } else if ((_move_food_y > 0 && _move_food_x > 0) && cnt == 7) {
//                --_move_food_y;
//                --_move_food_x;
//                scrR_lil.y = _cor_lil_food.first--;
//                scrR_lil.x = _cor_lil_food.second--;
//            }
//            cnt = (cnt == 7) ? 0 : cnt;
//        }
        scrR_lil.w = scrR_lil.h = 8;
        cnt++;
    }
}

std::pair<int, int> Food::getCorsLilFood() const {
    return _cor_lil_food;
}

std::pair<int, int> Food::getCorsBigFood() const {
    return _cor_big_food;
}

void Food::setCorsLilFood(std::pair<int, int> setCors) {
    _cor_lil_food = setCors;
}

void Food::setCorsBigFood(std::pair<int, int> setCors) {
    _cor_big_food = setCors;
}


void Food::DrawFood() {
    TextureManager::Draw(_texture_food_lil, scrR_lil);
}

Food::~Food() {

}