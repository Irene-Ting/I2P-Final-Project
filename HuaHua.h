#ifndef HUAHUA_H_INCLUDED
#define HUAHUA_H_INCLUDED

#include "Player.h"

class HuaHua : public Player
{
public:
    HuaHua() : Player()
    {
        step = 40;
        img = al_load_bitmap("./Material/Player2.png");
    }
};

#endif // HUAHUA_H_INCLUDED
