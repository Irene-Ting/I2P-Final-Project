#ifndef CANON_H_INCLUDED
#define CANON_H_INCLUDED

#include "Tower.h"

class Canon : public Tower
{
public:
    Canon(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
        type = CANON;

        square->r = 70;
        attack_frequency = 30;
        attack_velocity = 6;
        attack_harm_point = 15;
        img = al_load_bitmap("./Tower/Canon.png");
        attack_img = al_load_bitmap("./Tower/Canon_Beam.png");
    }

    int getWidth() override { return TowerWidth[CANON]; }
    int getHeight() override { return TowerHeight[CANON]; }
    std::vector<int> Utilize(int x, int y)
    {
        x/=40;
        y/=40;
        int gox[3] = {-1, 0, 1};
        int goy[3] = {-1, 0, 1};
        std::vector<int> change;
        for(int i = 0; i<3; ++i)
            for(int j = 0; j<3; ++j)
                change.push_back(x+gox[i]+(y+goy[j])*field_width/40);
        return change;
    }
};

#endif // CANON_H_INCLUDED
