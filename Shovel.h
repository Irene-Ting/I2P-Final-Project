#ifndef SHOVEL_H_INCLUDED
#define SHOVEL_H_INCLUDED
#include<vector>
#include "Tool.h"

class Shovel : public Tool
{
public:
    Shovel(int mouse_x, int mouse_y) : Tool(mouse_x, mouse_y)
    {
        type = SHOVEL;
        img = al_load_bitmap("./Tool/Shovel.png");
        sample = al_load_sample("./Music/bang_2.wav");
        toolSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(toolSound, ALLEGRO_PLAYMODE_ONCE);
    }

    int getWidth() override { return ToolWidth[SHOVEL]; }
    int getHeight() override { return ToolHeight[SHOVEL]; }
    std::vector<int> Utilize(int x, int y, double d)
    {
        al_attach_sample_instance_to_mixer(toolSound, al_get_default_mixer());
        al_stop_sample_instance(toolSound);
        al_play_sample_instance(toolSound);
        al_set_sample_instance_gain(toolSound, d);
        x/=40;
        y/=40;
        std::vector<int> change;
        for(int i = 0; i<field_height/40; ++i)
            change.push_back(i*field_width/40+x);
        return change;
    }
};

#endif // SHOVEL_H_INCLUDED
