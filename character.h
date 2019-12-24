#ifndef CHARACTER_H_INCLUDED
#define CHARACTER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "global.h"

class Character: public Object {
public:
    Character();
    ~Character();
    void Draw();
    void Load_Move(int);
private:
    int cur_x;
    int cur_y;
    int step;
};


#endif // MONSTER_H_INCLUDED
