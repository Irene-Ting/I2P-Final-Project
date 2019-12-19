#include "GameWindow.h"
#include <allegro5/allegro_audio.h>
#include <allegro5/allegro_acodec.h>

/*#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)*/

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    al_set_window_position(display, 200, 10);
    event_queue = al_create_event_queue();

    timer = al_create_timer(1.0 / FPS);

    if(timer == NULL)
        show_err_msg(-1);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    //al_init_font_addon(); // initialize the font addon
    //al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    //al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    //font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    //Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    //Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    game_init();
}

void
GameWindow::game_init()
{
    /*char buffer[50];
    sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
    tower[i] = al_load_bitmap(buffer);*/

    icon = al_load_bitmap("./icon.png");
    backgroundImg = al_load_bitmap("./background.png");

    /*startImg = al_load_bitmap("./background.png");
    endImg = al_load_bitmap("./background.png");
    burrowImg = al_load_bitmap("./background.png");
    softImg = al_load_bitmap("./background.png");
    hardImg = al_load_bitmap("./background.png");
    playerImg = al_load_bitmap("./background.png");*/

    al_set_display_icon(display, icon);
    //al_reserve_samples(3);

    sample = al_load_sample("");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    sample = al_load_sample("");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

    //Player *player = NULL;
    menu = new Menu();
    slider = new Slider();
    //slider->set_label_content("Volume");
}

void
GameWindow::game_reset()
{

}

void
GameWindow::game_play()
{
    int msg;
    srand(time(NULL));

    msg = -1;
    game_reset();
    game_begin();

    while(msg != GAME_EXIT)
    {
        msg = game_run();
    }
    show_err_msg(msg);
}

void
GameWindow::game_begin()
{
    //printf(">>> Start Level[%d]\n", level->getLevel());
    //draw_running_map();
    draw_start_map();

    al_play_sample_instance(startSound);
    while(al_get_sample_instance_playing(startSound));
}

int
GameWindow::game_run()
{
    int error = GAME_CONTINUE;

    if (!al_is_event_queue_empty(event_queue)) {

        error = process_event();
    }
    return error;
}

int
GameWindow::game_update()
{

}

void
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

void
GameWindow::game_destroy()
{

}

void
GameWindow::draw_running_map()
{

}

void draw_start_map()
{

}

int
GameWindow::process_event()
{

}
