#ifndef EXPLOSIVE_H_INCLUDED
#define EXPLOSIVE_H_INCLUDED

#include "Tool.h"

class Explosive : public Tool
{
public:
    Explosive(int mouse_x = 0, int mouse_y = 0) : Tool(mouse_x, mouse_y)
    {
        type = EXPLOSIVE;
        img = al_load_bitmap("./Tool/Explosive.png");
        sample = al_load_sample("./Music/bang_6.wav");
        toolSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(toolSound, ALLEGRO_PLAYMODE_ONCE);
    }

    int getWidth() override { return ToolWidth[EXPLOSIVE]; }
    int getHeight() override { return ToolHeight[EXPLOSIVE]; }
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
