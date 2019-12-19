#ifndef GAMEWINDOW_H_INCLUDED
#define GAMEWINDOW_H_INCLUDED
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

class GameWindow
{
public:
    GameWindow();

    void game_init();
    void game_reset();
    void game_play();
    void game_begin();

    int game_run();
    int game_update();

    void show_err_msg(int msg);
    void game_destroy();

    void draw_running_map();
    void draw_start_map();

    int process_event();

public:
    bool initial = true;

private:
    ALLEGRO_BITMAP *icon;
    ALLEGRO_BITMAP *backgroundImg = NULL;
    ALLEGRO_BITMAP *startImg = NULL;
    ALLEGRO_BITMAP *endImg = NULL;
    ALLEGRO_BITMAP *burrowImg;
    ALLEGRO_BITMAP *softImg;
    ALLEGRO_BITMAP *hardImg;
    ALLEGRO_BITMAP *playerImg;

    ALLEGRO_DISPLAY* display = NULL;
    //ALLEGRO_FONT *font = NULL;
    //ALLEGRO_FONT *Medium_font = NULL;
    //ALLEGRO_FONT *Large_font = NULL;

    ALLEGRO_EVENT_QUEUE *event_queue = NULL;
    ALLEGRO_EVENT event;
    ALLEGRO_TIMER *timer = NULL;

    ALLEGRO_SAMPLE *sample = NULL;
    ALLEGRO_SAMPLE_INSTANCE *startSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *digSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *walkSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *backgroundSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *winSound = NULL;
    ALLEGRO_SAMPLE_INSTANCE *loseSound = NULL;

    //LEVEL *level = NULL;

    /*Menu *menu = NULL;
    Slider *slider = NULL;
    Player *player = NULL;*/

    bool redraw = false;
    bool mute = false;

    //bool act = false;
    int scene = 0;
};


#endif // GAMEWINDOW_H_INCLUDED
