//
// Created by Kostiantyn MYKHAILENKO on 8/19/18.
//

#include "INibDisplay.hpp"

class Logic_game : public INibDisplay{
public:
    Logic_game();
    ~Logic_game();
    Logic_game(Logic_game const &rhs);
    Logic_game &operator=(Logic_game const & rhs);

    void init();
    void getEvent();
    void updateGameDate();
    void refreshDisplay();
    void stop();
};

#include "Logic_game.hpp"
