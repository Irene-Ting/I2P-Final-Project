#ifndef ARCHER_H_INCLUDED
#define ARCHER_H_INCLUDED

#include "Tower.h"

class Archer : public Tower
{
public:
    Archer(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
        type = ARCHER;
        img = al_load_bitmap("./Tower/Archer.png");
        sample = al_load_sample("./Music/bang_2.wav");
        toolSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(toolSound, ALLEGRO_PLAYMODE_ONCE);
    }

    int getWidth() override { return TowerWidth[ARCHER]; }
    int getHeight() override { return TowerHeight[ARCHER]; }
    std::vector<int> Utilize(int x, int y, double d)
    {
        al_attach_sample_instance_to_mixer(toolSound, al_get_default_mixer());
        al_stop_sample_instance(toolSound);
        al_play_sample_instance(toolSound);
        al_set_sample_instance_gain(toolSound, d);
        x/=40;
        y/=40;
        std::vector<int> change;
        for(int i = 0; i<field_width/40; ++i)
            change.push_back((y-ground/40)*field_width/40+i);
        return change;
    }
};

#endif // ARCHER_H_INCLUDED
