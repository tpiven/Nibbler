//
// Created by Kostiantyn MYKHAILENKO on 8/19/18.
//

#ifndef NIBBLER_INIBDISPLAY_HPP
#define NIBBLER_INIBDISPLAY_HPP

class INibDisplay{
public:
    virtual void init() = 0;//инициализация Любой либы
    virtual void getEvent() = 0;//ловим хуки от клавиш
    virtual void updateGameDate() = 0;//обновляем дату по хукам
    virtual void refreshDisplay() = 0;//перерисовка
    virtual void stop() = 0;//конец игры ???
};

#endif //NIBBLER_INIBDISPLAY_HPP
