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
#include "global.h"
#include "Slider.h"
class Menu : public Object
{
public:
    Menu();
    virtual ~Menu();

    void Reset();
    void Draw();
    int MouseIn(int, int);

    static bool isInRange(int, int, int);

    // Check if current coin is not less than needed coin
    bool Enough_Coin(int);
    void Change_Coin(int change) { Coin += change; }
    void Change_Time(int change) { Time += change; }
    void Change_Energy(int change) { EnergyPoint += change; }
    void Set_Level(int num) { level = num; }
    void Gain_Score(int n) {score+=n; };

    int getTowerCoin(int type) { return need_coin[type]; }
    int getTime() { return Time; }
    int getCoin() { return Coin; }
    int getEnergy() { return EnergyPoint; }
    int getLevel() {return level; }
    int getScore() {return score; }
    double getVolume() {return volume; }
    void adjustVolume(double d){volume = d;}
    void setPauseIcon();
    void setResumeIcon();

private:
    std::vector<ALLEGRO_BITMAP*> menu_tower;
    ALLEGRO_BITMAP *energy = NULL;
    ALLEGRO_BITMAP *coin = NULL;
    ALLEGRO_BITMAP *stopIcon = NULL;
    ALLEGRO_BITMAP *pauseIcon = NULL;
    ALLEGRO_FONT *menuFont;
    ALLEGRO_FONT *introFont;
    int EnergyPoint = 10;
    int Time = 0;
    int Coin = 0;
    int selectedTower = -1;
    int need_coin[NumOfToolType] = {-5, -10, -20, -30, -40};
    int level = 1;
    int score = 0;
    double volume = 1.0;
};

#endif // MENU_H_INCLUDED
