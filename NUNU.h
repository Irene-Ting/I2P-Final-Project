#ifndef NUNU_H_INCLUDED
#define NUNU_H_INCLUDED

#include "Player.h"

class Nunu : public Player
{
public:
    Nunu() : Player()
    {
        step = 40;
        img = al_load_bitmap("./Material/Player3.png");
    }
};

#endif // NUNU_H_INCLUDED
