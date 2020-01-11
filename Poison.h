#ifndef POISON_H_INCLUDED
#define POISON_H_INCLUDED

#include "Tower.h"

class Poison : public Tower
{
public:
    Poison(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
        type = POISON;

        //circle->r = 110;
        /*attack_frequency = 50;
        attack_velocity = 10;
        attack_harm_point = 3;*/
        img = al_load_bitmap("./Tower/Poison.png");
        //attack_img = al_load_bitmap("./Tower/Poison_Beam.png");
        sample = al_load_sample("./Music/bang_6.wav");
        toolSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(toolSound, ALLEGRO_PLAYMODE_ONCE);
    }

    int getWidth() override { return TowerWidth[POISON]; }
    int getHeight() override { return TowerHeight[POISON]; }
    std::vector<int> Utilize(int x, int y, double d)
    {
        al_attach_sample_instance_to_mixer(toolSound, al_get_default_mixer());
        al_stop_sample_instance(toolSound);
        al_play_sample_instance(toolSound);
        al_set_sample_instance_gain(toolSound, d);

        std::vector<int> change;
        for(int i = 0; i<field_width/40; ++i)
            for(int j = 0; j<field_height/40; ++j)
                change.push_back(j*field_width/40+i);
        return change;
    }

};

#endif // POISON_H_INCLUDED
