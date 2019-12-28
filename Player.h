#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "Object.h"

class Player: public Object {
public:
    Player();
    ~Player();
    void Draw();
    void Load_Move(int);
protected:
    int cur_x;
    int cur_y;
    int step;
};

#endif // PLAYER_H_INCLUDED
