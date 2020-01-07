#ifndef ARCHER_H_INCLUDED
#define ARCHER_H_INCLUDED

#include "Tower.h"

class Archer : public Tower
{
public:
    Archer(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
        type = ARCHER;

        square->r = 80;
        attack_frequency = 15;
        attack_velocity = 8;
        attack_harm_point = 7;
        img = al_load_bitmap("./Tower/Archer.png");
        attack_img = al_load_bitmap("./Tower/Archer_Beam.png");
    }

    int getWidth() override { return TowerWidth[ARCHER]; }
    int getHeight() override { return TowerHeight[ARCHER]; }
    std::vector<int> Utilize(int x, int y)
    {
        x/=40;
        y/=40;
        //vector<int> change;
        std::vector<int> change;
        for(int i = 0; i<field_height/40; ++i)
            change.push_back(i*field_width/40+x);
            //change[i] = (y-1)*15+i;
        return change;
    }
};

#endif // ARCHER_H_INCLUDED
