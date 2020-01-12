#ifndef DOKODEMO_H_INCLUDED
#define DOKODEMO_H_INCLUDED

#include "Tool.h"

class Dokodemo : public Tool
{
public:
    Dokodemo(int mouse_x = 0, int mouse_y = 0) : Tool(mouse_x, mouse_y)
    {
        type = DOKODEMO;
        img = al_load_bitmap("./Tool/Dokodemo.png");
        sample = al_load_sample("./Music/tool.wav");
        toolSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(toolSound, ALLEGRO_PLAYMODE_ONCE);
    }

    int getWidth() override { return ToolWidth[DOKODEMO]; }
    int getHeight() override { return ToolHeight[DOKODEMO]; }
    std::vector<int> Utilize(int x, int y, double d)
    {
        al_attach_sample_instance_to_mixer(toolSound, al_get_default_mixer());
        al_stop_sample_instance(toolSound);
        al_play_sample_instance(toolSound);
        al_set_sample_instance_gain(toolSound, d);
        while(al_get_sample_instance_playing(toolSound));
        x/=40;
        y/=40;
        std::vector<int> change;
        change.push_back((y-ground/40)*field_width/40+x);
        return change;
    }
};

#endif // DOKODEMO_H_INCLUDED
