#ifndef PLAYER1_H_INCLUDED
#define PLAYER1_H_INCLUDED

#include "Player.h"

class Player1 : public Player
{
public:
    Player1() : Player()
    {
        step = 20;
    }
};

#endif // PLAYER1_H_INCLUDED
