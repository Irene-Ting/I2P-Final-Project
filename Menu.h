#ifndef MENU_H_INCLUDED
#define MENU_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <vector>
#include "Object.h"
#include "Square.h"
#include "global.h"
#include "Slider.h"
class Menu : public Object
{
public:
    Menu();
    virtual ~Menu();

    void Reset();
    void Draw();

    // Detect if cursor hovers over any of tower on menu
    // If so, return its type
    // Otherwise, return -1
    int MouseIn(int, int);

    // static function that detect if one point is on a line
    // This function is just used to simplify "MouseIn"
    static bool isInRange(int, int, int);

    // Check if current coin is not less than needed coin
    bool Enough_Coin(int);
    void Change_Coin(int change) { Coin += change; }
    void Change_Time(int change) { Time += change; }
    void Change_Energy(int change) { EnergyPoint += change; }
    bool Subtract_HP(int escapeNum = 1);
    void Gain_Score(int);

    int getTowerCoin(int type) { return need_coin[type]; }
    int getTime() { return Time; }
    int getCoin() { return Coin; }
    int getEnergy() { return EnergyPoint; }
    int getKilled() { return killedMonster; }

private:
    std::vector<ALLEGRO_BITMAP*> menu_tower;
    ALLEGRO_BITMAP *energy = NULL;
    ALLEGRO_BITMAP *coin = NULL;
    ALLEGRO_FONT *menuFont;
    int EnergyPoint = 10;
    int killedMonster = 0;
    int Time = 0;
    int Coin = 0;
    int selectedTower = -1;
    int need_coin[Num_TowerType] = {-5, -10, -20, -40, -70, -30};
};

#endif // MENU_H_INCLUDED
