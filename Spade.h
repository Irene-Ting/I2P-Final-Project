#ifndef SPADE_H_INCLUDED
#define SPADE_H_INCLUDED

#include "Tool.h"

class Spade : public Tool
{
public:
    Spade(int mouse_x = 0, int mouse_y = 0) : Tool(mouse_x, mouse_y)
    {
        type = SPADE;
        img = al_load_bitmap("./Tool/Spade.png");
        sample = al_load_sample("./Music/bang_2.wav");
        toolSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(toolSound, ALLEGRO_PLAYMODE_ONCE);
    }

    int getWidth() override { return ToolWidth[SPADE]; }
    int getHeight() override { return ToolHeight[SPADE]; }
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

#endif // SPADE_H_INCLUDED
