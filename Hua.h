#ifndef HUA_H_INCLUDED
#define HUA_H_INCLUDED

#include "Player.h"

class Hua : public Player
{
public:
    Hua() : Player()
    {
        step = 40;
        img = al_load_bitmap("./Material/Player2.png");
    }
};

#endif // HUA_H_INCLUDED
