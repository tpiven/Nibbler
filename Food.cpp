#include "Food.hpp"
#include "glob.hpp"
int g_weight;
int g_height;


Food::Food(const char *lil_food, const char *big_food){
    _texture_food_lil = TextureManager::LoadTexture(big_food);
    _texture_food_big = TextureManager::LoadTexture(big_food);
    _cor_lil_food = std::make_pair(-1, -1);
    _cor_big_food = std::make_pair(-1, -1);
}

void Food::mandatoryFood(int (*m_map)[67][90]){
    if (_cor_lil_food.first == -1 || _cor_lil_food.second == -1){
        srand(time(NULL));
        while(_cor_lil_food.first == -1 || _cor_lil_food.second == -1){
            _cor_lil_food.first = rand() % g_height;
            _cor_lil_food.second = rand() % g_weight;
            if ((*m_map)[(_cor_lil_food.first * 67 / g_height) - 1][(_cor_lil_food.second * 90 / g_weight) - 1] != 0)
                _cor_lil_food.first = _cor_lil_food.second = -1;
        }
        scrR_lil.w = scrR_lil.h = 8;
        scrR_lil.y = _cor_lil_food.first;
        scrR_lil.x = _cor_lil_food.second;
    }
}

void Food::DrawFood() {
    TextureManager::Draw(_texture_food_lil, scrR_lil);
}

Food::~Food() {
}