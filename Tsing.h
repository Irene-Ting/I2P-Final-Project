#ifndef TSING_H_INCLUDED
#define TSING_H_INCLUDED

#include "Player.h"

class Tsing : public Player
{
public:
    Tsing() : Player()
    {
        step = 40;
        img = al_load_bitmap("./Material/Tsing.png");
    }
};

#endif // TSING_H_INCLUDED
