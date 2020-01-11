#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED

#include <stdio.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include "Object.h"
#include "Circle.h"
#include "global.h"
#include "Object.h"
#include "level.h"
#include "Menu.h"

enum {LEFT=0, RIGHT, UP, DOWN};

class Player: public Object {
public:
    Player();
    ~Player();
    void Draw();
    bool Load_Move(Node*, Menu*, int);
    int getWidth() { return 40; }
    int getHeight() { return 40; }
    void goHere(Node*, Menu*, int, int);
    void adjustVolume(double);
protected:
    int cur_x;
    int cur_y;
    int step;
    ALLEGRO_BITMAP *img;
private:
    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *walkSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *softSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *coinSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *energySound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *hitSound = NULL;
};

#endif // PLAYER_H_INCLUDED
