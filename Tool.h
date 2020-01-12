#ifndef TOOL_H_INCLUDED
#define TOOL_H_INCLUDED

#include <stdio.h>
#include <vector>
#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include "Object.h"
#include "global.h"

class Tool : public Object
{
public:
    Tool(int, int);
    virtual ~Tool();

    // override virtual function "Object::Draw"
    void Draw();
    void ToggleClicked() { isClicked = !isClicked; }
    virtual std::vector<int> Utilize(int x, int y, double){ return {0};}

    virtual int getWidth() { return 40; }
    virtual int getHeight() { return 40; }

    // show selected tower image on cursor position
    static void SelectedTower(int, int, int);

protected:
    int type;
    bool isClicked = false;
    ALLEGRO_BITMAP *img;
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *toolSound = NULL;
};

#endif // TOOL_H_INCLUDED
