#ifndef STORM_H_INCLUDED
#define STORM_H_INCLUDED

#include "Tower.h"

class Storm : public Tower
{
public:
    Storm(int mouse_x = 0, int mouse_y = 0) : Tower(mouse_x, mouse_y)
    {
        type = STORM;

        //circle->r = 150;
        /*attack_frequency = 5;
        attack_velocity = 20;
        attack_harm_point = 5;*/
        img = al_load_bitmap("./Tower/Storm.png");
        //attack_img = al_load_bitmap("./Tower/Storm_Beam.png");
        sample = al_load_sample("./Music/tool.wav");
        toolSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(toolSound, ALLEGRO_PLAYMODE_ONCE);
    }

    int getWidth() override { return TowerWidth[STORM]; }
    int getHeight() override { return TowerHeight[STORM]; }
    std::vector<int> Utilize(int x, int y, double d)
    {
        al_attach_sample_instance_to_mixer(toolSound, al_get_default_mixer());
        al_stop_sample_instance(toolSound);
        al_play_sample_instance(toolSound);
        al_set_sample_instance_gain(toolSound, d);
        while(al_get_sample_instance_playing(toolSound));
        x/=40;
        y/=40;
        //vector<int> change;
        std::vector<int> change;
        change.push_back((y-ground/40)*field_width/40+x);
        return change;
    }
};

#endif // STORM_H_INCLUDED
