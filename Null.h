#ifndef NULL_H_INCLUDED
#define NULL_H_INCLUDED

#include "Player.h"

class Null : public Player
{
public:
    Null() : Player()
    {
        step = 40;
        img = al_load_bitmap("./Material/Null.png");
    }
};

#endif // NULL_H_INCLUDED
