#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED
#include <ctime>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <time.h>
#include "Menu.h"
#include "Level.h"
#include "WolfKnight.h"
#include "CaveMan.h"
#include "Wolf.h"
#include "DemonNijia.h"
#include "Ntower.h"
#include "Arcane.h"
#include "Archer.h"
#include "Canon.h"
#include "Poison.h"
#include "Storm.h"
#include "Attack.h"
#include "Slider.h"
#include "Player1.h"
#include "Hua.h"
#include "HuaHua.h"
#include "NUNU.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7

enum {ACTIVATE = 0, GAMERUN, GAMEWIN, GAMELOSE};

// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 4;

// 1 coin every 2 seconds
const int TimeSpeed = FPS;
const int EnergySpeed = FPS*10;
const int Time_Gain = 1;

class GameWindow
{
public:
    // constructor
    GameWindow();
    // each process of scene
    //void game_prepare();
    void game_init();
    void game_reset();
    void game_play();
    void game_begin();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

    // each drawing scene function
    void draw_running_map();
    void draw_start_map();
    void draw_win_map();
    void draw_lose_map();
    // process of updated event
    int process_event();
    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);
    // detect if a tower will be constructed on road
    bool isAbove();
    bool pauseClicked();
    bool stopClicked();

    Tower* create_tower(int);
    Player* create_player(int);
    //Monster* create_monster();

public:
    bool initial = true;

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *tower[Num_TowerType];
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *themeImg = NULL;
    ALLEGRO_BITMAP *finish = NULL;
    ALLEGRO_BITMAP *start_page = NULL;
    ALLEGRO_BITMAP *win_page = NULL;
    ALLEGRO_BITMAP *lose_page = NULL;
    ALLEGRO_BITMAP *path;
    ALLEGRO_BITMAP *softImg;
    ALLEGRO_BITMAP *hardImg;
    ALLEGRO_BITMAP *coinImg;
    ALLEGRO_BITMAP *energyImg;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *font = NULL;
    ALLEGRO_FONT *Medium_font = NULL;
    ALLEGRO_FONT *Large_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;
    //ALLEGRO_TIMER *monster_pro = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
    //ALLEGRO_SAMPLE_INSTANCE *clearSound = NULL;
    //ALLEGRO_SAMPLE_INSTANCE *failSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *gapSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *winSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *loseSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *alarm = NULL;

    LEVEL *level = NULL;
    Menu *menu = NULL;
    Slider *slider_back = NULL;
    Slider *slider_eff = NULL;
    Player *player = NULL;
    //std::vector<Monster*> monsterSet;
    //std::list<Tower*> towerSet;

    //int Monster_Pro_Count = 0;
    //int Coin_Inc_Count = 0;
    int Time_Inc_Count = 0;
    int Energy_Inc_Count = 0;
    int mouse_x, mouse_y;
    int selectedTower = -1, lastClicked = -1;

    bool redraw = false;
    bool mute = false;
    bool win = false;
    //bool act = false;
    int scene = 0;
    int theme = 1;
};


#endif // MAINWINDOW_H_INCLUDED
