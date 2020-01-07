#ifndef ARCANE_H_INCLUDED
#define ARCANE_H_INCLUDED
#include<vector>
#include "Tower.h"

class Arcane : public Tower
{
public:
    Arcane(int mouse_x, int mouse_y) : Tower(mouse_x, mouse_y)
    {
        type = ARCANE;

        square->r = 80;
        attack_frequency = 20;
        attack_velocity = 8;
        attack_harm_point = 5;
        img = al_load_bitmap("./Tower/Arcane.png");
        attack_img = al_load_bitmap("./Tower/Arcane_Beam.png");
    }

    int getWidth() override { return TowerWidth[ARCANE]; }
    int getHeight() override { return TowerHeight[ARCANE]; }
    std::vector<int> Utilize(int x, int y)
    {
        x/=40;
        y/=40;
        //vector<int> change;
        std::vector<int> change;
        for(int i = 0; i<field_width/40; ++i)
            change.push_back((y-3)*field_width/40+i);
            //change[i] = (y-1)*15+i;
        return change;
    }
};

#endif // ARCANE_H_INCLUDED
