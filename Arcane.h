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

        //square->r = 80;
        /*attack_frequency = 20;
        attack_velocity = 8;
        attack_harm_point = 5;*/
        img = al_load_bitmap("./Tower/Arcane.png");
        //attack_img = al_load_bitmap("./Tower/Arcane_Beam.png");
        sample = al_load_sample("./Music/bang_2.wav");
        toolSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(toolSound, ALLEGRO_PLAYMODE_ONCE);
    }

    int getWidth() override { return TowerWidth[ARCANE]; }
    int getHeight() override { return TowerHeight[ARCANE]; }
    std::vector<int> Utilize(int x, int y)
    {
        al_attach_sample_instance_to_mixer(toolSound, al_get_default_mixer());
        al_stop_sample_instance(toolSound);
        al_play_sample_instance(toolSound);
        x/=40;
        y/=40;
        //vector<int> change;
        std::vector<int> change;
        for(int i = 0; i<field_width/40; ++i)
            change.push_back((y-ground/40)*field_width/40+i);
        return change;
    }
};

#endif // ARCANE_H_INCLUDED
