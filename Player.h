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
#include "level.h"
#include "Menu.h"

class Player: public Object {
public:
    Player();
    ~Player();
    void Draw();
    bool Load_Move(Node*, Menu*, int);
    int getWidth() { return 40; }
    int getHeight() { return 40; }
protected:
    int cur_x;
    int cur_y;
    int step;
    ALLEGRO_BITMAP *img;
};

#endif // PLAYER_H_INCLUDED
