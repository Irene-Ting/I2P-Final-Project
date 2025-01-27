#ifndef MAINWINDOW_H_INCLUDED
#define MAINWINDOW_H_INCLUDED
#include <ctime>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>
#include <vector>
#include <list>
#include <time.h>
#include "Menu.h"
#include "Level.h"
#include "Shovel.h"
#include "Spade.h"
#include "Bomb.h"
#include "Explosive.h"
#include "Dokodemo.h"
#include "Slider.h"
#include "Tsing.h"
#include "Hua.h"
#include "Null.h"

#define GAME_INIT -1
#define GAME_SETTING 0
#define GAME_SELECT 1
#define GAME_BEGIN 2
#define GAME_CONTINUE 3
#define GAME_FAIL 4
#define GAME_TERMINATE 5
#define GAME_NEXT_LEVEL 6
#define GAME_EXIT 7

enum {ACTIVATE = 0, GAMERUN, GAMEWIN, GAMELOSE, INSTRUCTION};

// clock rate
const float FPS = 60;

// total number of level
const int LevelNum = 3;

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
    void show_instruction(int);
    // process of updated event
    int process_event();
    // detect if mouse hovers over a rectangle
    bool mouse_hover(int, int, int, int);
    bool isAbove();
    bool pauseClicked();
    bool stopClicked();
    bool infoClicked();

    Tool* create_tool(int);
    Player* create_player(int);

public:
    bool initial = true;

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *tool[NumOfToolType];
    ALLEGRO_BITMAP *background = NULL;
    ALLEGRO_BITMAP *themeImg = NULL;
    ALLEGRO_BITMAP *finish = NULL;
    ALLEGRO_BITMAP *start = NULL;
    ALLEGRO_BITMAP *start_page = NULL;
    ALLEGRO_BITMAP *win_page = NULL;
    ALLEGRO_BITMAP *lose_page = NULL;
    ALLEGRO_BITMAP *path = NULL;;
    ALLEGRO_BITMAP *softImg = NULL;;
    ALLEGRO_BITMAP *hardImg = NULL;;
    ALLEGRO_BITMAP *coinImg = NULL;;
    ALLEGRO_BITMAP *energyImg = NULL;;
    ALLEGRO_BITMAP *instructionImg = NULL;
    ALLEGRO_BITMAP *playerImg = NULL;
    ALLEGRO_BITMAP *talkImg = NULL;
    ALLEGRO_BITMAP *sourceImg = NULL;

    ALLEGRO_DISPLAY* display = NULL;
    ALLEGRO_FONT *Large_font = NULL;
    ALLEGRO_FONT *OJ_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer_d = NULL;
    ALLEGRO_TIMER *timer_g = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
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

    int Time_Inc_Count = 0;
    int Energy_Inc_Count = 0;
    int mouse_x, mouse_y;
    int selectedTool = -1, lastClicked = -1;

    bool redraw = false;
    bool mute = false;
    bool win = false;
    int scene = 0;
    int theme = 1;
};

#endif // MAINWINDOW_H_INCLUDED
