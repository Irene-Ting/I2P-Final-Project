#ifndef NTOWER_H_INCLUDED
#define NTOWER_H_INCLUDED

#include "Tower.h"

class Ntower : public Tower
{
public:
    Ntower(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
        type = NTOWER;

        circle->r = 90;
        attack_frequency = 120;
        attack_velocity = 5;
        attack_harm_point = 10;
        img = al_load_bitmap("./Tower/Ntower.png");
        attack_img = al_load_bitmap("./Tower/Ntower_Beam.jpg");
    }

    int getWidth() override { return TowerWidth[NTOWER]; }
    int getHeight() override { return TowerHeight[NTOWER]; }
};

#endif // ARCHER_H_INCLUDED
