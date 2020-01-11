#ifndef CANON_H_INCLUDED
#define CANON_H_INCLUDED

#include "Tower.h"

class Canon : public Tower
{
public:
    Canon(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
        type = CANON;

        //square->r = 70;
        /*attack_frequency = 30;
        attack_velocity = 6;
        attack_harm_point = 15;*/
        img = al_load_bitmap("./Tower/Canon.png");
        //attack_img = al_load_bitmap("./Tower/Canon_Beam.png");
        sample = al_load_sample("./Music/bang_6.wav");
        toolSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(toolSound, ALLEGRO_PLAYMODE_ONCE);
    }

    int getWidth() override { return TowerWidth[CANON]; }
    int getHeight() override { return TowerHeight[CANON]; }
    std::vector<int> Utilize(int x, int y, double d)
    {
        al_attach_sample_instance_to_mixer(toolSound, al_get_default_mixer());
        al_stop_sample_instance(toolSound);
        al_play_sample_instance(toolSound);
        al_set_sample_instance_gain(toolSound, d);
        x/=40;
        y/=40;
        int gox[3] = {-1, 0, 1};
        int goy[3] = {-1, 0, 1};
        std::vector<int> change;
        for(int i = 0; i<3; ++i)
            for(int j = 0; j<3; ++j)
            {
                if(x+gox[i]>=0 && x+gox[i]<field_width/40 && y-ground/40+goy[j]>=0 && y-ground/40+goy[j]<field_width/40)
                {
                    change.push_back(x+gox[i]+(y-ground/40+goy[j])*field_width/40);
                }
            }

        return change;
    }
};

#endif // CANON_H_INCLUDED
