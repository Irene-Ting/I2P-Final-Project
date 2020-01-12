#include "GameWindow.h"
#include "global.h"
#include "Level.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)

const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

bool random(int);
int ran[1000];// store the random numbers

void
GameWindow::game_init()
{
    char buffer[50];
    level = new LEVEL(1);
    menu = new Menu();
    slider_back = new Slider(field_width+12, 525);
    slider_eff = new Slider(field_width+12, 575);
    slider_back->set_label_content("Background Sound");
    slider_eff->set_label_content("Effect Sound");

    icon = al_load_bitmap("./icon.png");
    win_page = al_load_bitmap("./Material/youWin.png");
    lose_page = al_load_bitmap("./Material/youLose.png");
    start_page = al_load_bitmap("./Material/Start.png");
    background = al_load_bitmap("./Material/Background.png");
    finish = al_load_bitmap("./Material/end_60.png");
    start = al_load_bitmap("./Material/start_60.png");

    for(int i = 0; i < Num_TowerType; i++)
    {
        sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
        tower[i] = al_load_bitmap(buffer);
    }

    srand(time(NULL));
    for(int i = 0; i<1000; ++i) ran[i] = rand()%100;

    al_set_display_icon(display, icon);
    al_reserve_samples(10);///?
    sample = al_load_sample("./Music/Intro.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    sample = al_load_sample("./Music/gameWin.wav");
    winSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(winSound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(winSound, al_get_default_mixer());

    sample = al_load_sample("./Music/gameLose.wav");
    loseSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(loseSound, ALLEGRO_PLAYMODE_LOOP);
    al_attach_sample_instance_to_mixer(loseSound, al_get_default_mixer());

    sample = al_load_sample("./Music/phone.wav");
    alarm = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(alarm, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(alarm, al_get_default_mixer());

    al_start_timer(timer_d);
}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;
    return false;
}

bool
GameWindow::isAbove()
{
    if(mouse_x > 0 && mouse_x < field_width && mouse_y > ground && mouse_y < ground+field_height)
        return false;
    return true;
}

bool
GameWindow::pauseClicked()
{
    if((mouse_x-(field_width+28))*(mouse_x-(field_width+28))+(mouse_y-460)*(mouse_y-460)<=400)
        return true;
    return false;
}
bool
GameWindow::stopClicked()
{
    if((mouse_x-(field_width+74))*(mouse_x-(field_width+74))+(mouse_y-460)*(mouse_y-460)<=400)
        return true;
    return false;
}
Tower*
GameWindow::create_tower(int type)
{
    Tower *t = NULL;

    if(isAbove())
        return t;
    switch(type)
    {
    case ARCANE:
        t = new Arcane(mouse_x, mouse_y);
        break;
    case ARCHER:
        t = new Archer(mouse_x, mouse_y);
        break;
    case CANON:
        t = new Canon(mouse_x, mouse_y);
        break;
    case POISON:
        t = new Poison(mouse_x, mouse_y);
        break;
    case STORM:
        t = new Storm(mouse_x, mouse_y);
        break;
    default:
        break;
    }

    menu->Change_Coin(menu->getTowerCoin(type));

    return t;
}

Player*
GameWindow::create_player(int type)
{
    Player *p = NULL;

    switch(type)
    {
    case PLAYER1:
        p = new Player1();
        break;
    case HuaHua:
        p = new Hua();
        break;
    case NUNU:
        p = new Nunu();
        break;

    default:
        break;
    }
    return p;
}

void
GameWindow::game_play()
{
    int msg;
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
GameWindow::show_err_msg(int msg)
{
    if(msg == GAME_TERMINATE)
        fprintf(stderr, "Game Terminated...");
    else
        fprintf(stderr, "unexpected msg: %d", msg);

    game_destroy();
    exit(9);
}

GameWindow::GameWindow()
{
    if (!al_init())
        show_err_msg(-1);

    printf("Game Initializing...\n");

    display = al_create_display(window_width, window_height);
    al_set_window_position(display, 10, 10);
    event_queue = al_create_event_queue();

    timer_d = al_create_timer(1.0 / FPS);
    timer_g = al_create_timer(1.0 / FPS);

    if (display == NULL || event_queue == NULL)
        show_err_msg(-1);

    al_init_primitives_addon();
    al_init_font_addon(); // initialize the font addon
    al_init_ttf_addon(); // initialize the ttf (True Type Font) addon
    al_init_image_addon(); // initialize the image addon
    al_init_acodec_addon(); // initialize acodec addon

    al_install_keyboard(); // install keyboard event
    al_install_mouse();    // install mouse event
    al_install_audio();    // install audio event

    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font
    OJ_font = al_load_ttf_font("Helvetica.ttf", 26, 0);

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer_d));
    al_register_event_source(event_queue, al_get_timer_event_source(timer_g));

    game_init();
}

void
GameWindow::game_begin()
{
    printf(">>> Start Level[%d]\n", level->getLevel());
    menu->Set_Level(level->getLevel());
    char buffer[50];
    win = false;

    if(scene==ACTIVATE)
    {
        al_play_sample_instance(startSound);
        level->setLevel(1);
        draw_start_map();
    }
    else
    {
        for(int i = 0; i<NumOfGrid; ++i)
        {
            level->levelMap[i].func = NORMAL;
            if(level->levelMap[i].type==PATH && i!=2)
            {
                if(random(5))
                    level->levelMap[i].func = ENERGY;
            }
            else if(level->levelMap[i].type==SOFT)
            {
                if(random(10)) level->levelMap[i].func = COIN;
            }
        }
        player = create_player(theme);
        sprintf(buffer, "./Material/path%d.png", theme);
        path = al_load_bitmap(buffer);
        sprintf(buffer, "./Material/soft%d.png", theme);
        softImg = al_load_bitmap(buffer);
        sprintf(buffer, "./Material/hard%d.png", theme);
        hardImg = al_load_bitmap(buffer);
        sprintf(buffer, "./Material/money%d.png", theme);
        coinImg = al_load_bitmap(buffer);
        sprintf(buffer, "./Material/energy%d.png", theme);
        energyImg = al_load_bitmap(buffer);
        sprintf(buffer, "./Material/theme%d.png", theme);
        themeImg = al_load_bitmap(buffer);

        draw_running_map();

        sprintf(buffer, "./Music/Theme%dgap.wav", theme);
        sample = al_load_sample(buffer);
        gapSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(gapSound, ALLEGRO_PLAYMODE_ONCE);
        al_attach_sample_instance_to_mixer(gapSound, al_get_default_mixer());

        sprintf(buffer, "./Music/Theme%dLevel%d.wav", theme, level->getLevel());
        sample = al_load_sample(buffer);
        backgroundSound = al_create_sample_instance(sample);
        al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_LOOP);
        al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());
        al_play_sample_instance(backgroundSound);
        al_set_sample_instance_gain(backgroundSound, slider_back->getDegree());
        al_set_sample_instance_gain(gapSound, slider_back->getDegree());
        al_set_sample_instance_gain(alarm, slider_eff->getDegree());
        player->adjustVolume(slider_eff->getDegree());
        menu->adjustVolume(slider_eff->getDegree());

        al_start_timer(timer_g);
        al_start_timer(timer_d);
        al_register_event_source(event_queue, al_get_keyboard_event_source());
    }
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

void
GameWindow::game_reset()
{
    selectedTower = -1;
    lastClicked = -1;
    Time_Inc_Count = 0;
    Energy_Inc_Count = 0;
    mute = false;
    redraw = false;
    scene = ACTIVATE;
    menu->Reset();
    win = false;
    al_stop_sample_instance(startSound);
    al_stop_timer(timer_d);
    al_stop_timer(timer_g);
}

void
GameWindow::game_destroy()
{
    game_reset();

    al_destroy_display(display);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font);
    al_destroy_font(Medium_font);
    al_destroy_font(Large_font);
    al_destroy_font(OJ_font);

    al_destroy_timer(timer_d);
    al_destroy_timer(timer_g);

    for(int i=0;i<5; i++)
        al_destroy_bitmap(tower[i]);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);
    delete slider_back;
    delete slider_eff;
    delete level;
    delete menu;
    delete player;
}

int
GameWindow::process_event()
{
    int instruction = GAME_CONTINUE;
    int coin_bef = menu->getCoin();
    int energy_bef = menu->getEnergy();
    al_wait_for_event(event_queue, &event);
    redraw = false;

    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer_d) {
            redraw = true;
        }
        else if(event.timer.source == timer_g)
        {
            if(Time_Inc_Count==0)
                menu->Change_Time(1);
            Time_Inc_Count = (Time_Inc_Count + 1) % TimeSpeed;

            if(Energy_Inc_Count==0)
                menu->Change_Energy(-1);
            Energy_Inc_Count = (Energy_Inc_Count + 1) % EnergySpeed;

            if(menu->getEnergy()<=0) scene = GAMELOSE;
            else if(menu->getEnergy()<=5)
            {
                if(!al_get_sample_instance_playing(alarm))
                    al_play_sample_instance(alarm);
            }
            else if(menu->getEnergy()>5)
            {
                if(al_get_sample_instance_playing(alarm))
                    al_stop_sample_instance(alarm);
            }
        }
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else
    {
        switch(scene)
        {
            case ACTIVATE:
                if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    mouse_x = event.mouse.x;
                    mouse_y = event.mouse.y;
                    bool func = false;
                    if(mouse_hover(60, 200, 336, 225))
                    {
                        func = true;
                        theme = 1;
                    }
                    else if(mouse_hover(60+3.1*120, 200, 336, 225))
                    {
                        func = true;
                        theme = 2;
                    }
                    else if(mouse_hover(60+6.2*120, 200, 336, 225))
                    {
                        func = true;
                        theme = 3;
                    }

                    if(func)
                    {
                        scene++;
                        al_stop_sample_instance(startSound);
                        game_begin();
                    }
                }
                break;
            case GAMERUN:
                if(event.type == ALLEGRO_EVENT_KEY_DOWN && al_get_timer_started(timer_g)) {
                    switch(event.keyboard.keycode) {
                        case ALLEGRO_KEY_LEFT:
                            win = player->Load_Move(level->levelMap, menu, LEFT);
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            win = player->Load_Move(level->levelMap, menu, RIGHT);
                            break;
                        case ALLEGRO_KEY_UP:
                            win = player->Load_Move(level->levelMap, menu, UP);
                            break;
                        case ALLEGRO_KEY_DOWN:
                            win = player->Load_Move(level->levelMap, menu, DOWN);
                            break;
                    }
                }
                else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {

                        if(al_get_timer_started(timer_g)) selectedTower = menu->MouseIn(mouse_x, mouse_y);
                        if(slider_back->isClicked(mouse_x, mouse_y))
                        {
                            slider_back->toggleDrag();
                        }
                        else if(slider_eff->isClicked(mouse_x, mouse_y))
                        {
                            slider_eff->toggleDrag();
                        }
                        else if(pauseClicked())
                        {
                            if(al_get_timer_started(timer_g))
                            {
                                menu->setResumeIcon();
                                al_stop_timer(timer_g);
                            }
                            else
                            {
                                menu->setPauseIcon();
                                al_start_timer(timer_g);
                            }
                        }
                        else if(stopClicked())
                        {
                            scene = GAMELOSE;
                        }
                    }
            else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                if(selectedTower != -1){
                    Tower *t = create_tower(selectedTower);
                    if(t == NULL)
                    {
                        printf("Wrong place\n");
                    }
                    else {
                        al_stop_timer(timer_g);
                        al_unregister_event_source(event_queue, al_get_keyboard_event_source());
                        std::vector<int> change;
                        change = t->Utilize(mouse_x, mouse_y, menu->getVolume());
                        for(auto i : change)
                        {
                            if(i>=0 && i<=NumOfGrid)
                            {
                                if(level->levelMap[i].type == HARD)
                                    if(random(2)) level->levelMap[i].func = COIN;
                                level->levelMap[i].type = PATH;
                            }
                        }
                        if(selectedTower==4) win = player->goHere(level->levelMap, menu, mouse_x/40, mouse_y/40);
                        al_start_timer(timer_g);
                        al_register_event_source(event_queue, al_get_keyboard_event_source());
                    }
                    menu->MouseIn(field_width/2, field_height/2);
                    selectedTower = -1;

                }
                else if(slider_back->isDragged())
                {
                    slider_back->toggleDrag();
                }
                else if(slider_eff->isDragged())
                {
                    slider_eff->toggleDrag();
                }
            }
            else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
                if(slider_back->isDragged())
                {
                    slider_back->Drag(mouse_x, mouse_y);
                    al_set_sample_instance_gain(backgroundSound, slider_back->getDegree());
                    al_set_sample_instance_gain(gapSound, slider_back->getDegree());
                }
                if(slider_eff->isDragged())
                {
                    slider_eff->Drag(mouse_x, mouse_y);
                    al_set_sample_instance_gain(alarm, slider_eff->getDegree());
                    player->adjustVolume(slider_eff->getDegree());
                    menu->adjustVolume(slider_eff->getDegree());
                }
            }
                break;
            case GAMEWIN:
                if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    mouse_x = event.mouse.x;
                    mouse_y = event.mouse.y;
                    if(mouse_hover(550, 100, 350, 170))
                    {
                        scene = ACTIVATE;
                        al_stop_sample_instance(winSound);
                        game_play();
                    }
                    else if(mouse_hover(550, 330, 350, 170))
                    {
                        return GAME_EXIT;
                    }
                }
                break;
            case GAMELOSE:
                if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    mouse_x = event.mouse.x;
                    mouse_y = event.mouse.y;
                    if(mouse_hover(550, 100, 350, 170))
                    {
                        scene = ACTIVATE;
                        al_stop_sample_instance(loseSound);
                        game_play();
                    }
                    else if(mouse_hover(550, 330, 350, 170))
                    {
                        return GAME_EXIT;
                    }
                }
                break;

            }
    }

    if(menu->getCoin()>coin_bef)
    {
        menu->Gain_Score((menu->getCoin()-coin_bef)*level->getLevel());
    }

    if(menu->getEnergy()>energy_bef)
    {
        menu->Gain_Score((menu->getEnergy()-energy_bef)*level->getLevel());
    }

    if(redraw) {
        if(scene==GAMERUN)
        {
            draw_running_map();
            if(win)
            {
                int curLevel = level->getLevel();
                al_stop_sample_instance(backgroundSound);
                al_stop_timer(timer_g);
                al_unregister_event_source(event_queue, al_get_keyboard_event_source());
                al_play_sample_instance(gapSound);
                while(al_get_sample_instance_playing(gapSound));
                if(curLevel<3)
                {
                    level->setLevel(curLevel+1);
                    game_begin();
                }
                else scene = GAMEWIN;
            }
        }

        else if(scene==ACTIVATE)
        {
            draw_start_map();
        }
        else if(scene==GAMEWIN)
        {
            draw_win_map();
        }
        else if(scene==GAMELOSE)
        {
            draw_lose_map();
        }
        redraw = false;
    }

    return instruction;
}

void
GameWindow::draw_running_map()
{
    unsigned int i, j;

    al_draw_bitmap(background, 0, 0, 0);
    al_draw_bitmap(themeImg, 0, 0, 0);

    if(theme==3)
    {
        char buffer[] = "NTHU Online Judge    Contest    Problem    Submit    Status";
        al_draw_text(OJ_font, WHITE, 15, 15, ALLEGRO_ALIGN_LEFT, buffer);
    }
    al_draw_bitmap(finish, 21.7*grid_width, 60, 0);
    al_draw_bitmap(start, 1.7*grid_width, 60, 0);
    for(i = 0; i < field_height/40; i++)
    {
        for(j = 0; j < field_width/40; j++)
        {
            char buffer[50];
            //sprintf(buffer, "%d", i*field_width/40 + j);
            switch(level->levelMap[i*field_width/40 + j].type)
            {
                //printf("here");
                case PATH:
                    al_draw_bitmap(path, j*40, ground+i*40, 0);
                    break;
                case SOFT:
                    al_draw_bitmap(softImg, j*40, ground+i*40, 0);
                    break;
                case HARD:
                    al_draw_bitmap(hardImg, j*40, ground+i*40, 0);
                    break;
            }
            switch(level->levelMap[i*field_width/40+j].func)
            {
                case ENERGY:;
                    al_draw_bitmap(energyImg, j*40, ground+i*40, 0);
                    break;
                case COIN:
                    al_draw_bitmap(coinImg, j*40, ground+i*40, 0);
                    break;

            }
        }
    }

    menu->Draw();
    slider_back->Draw();
    slider_eff->Draw();
    if(selectedTower != -1)
        Tower::SelectedTower(mouse_x, mouse_y, selectedTower);
    player->Draw();
    al_flip_display();
}

void
GameWindow::draw_start_map()
{
    //al_clear_to_color(BLACK);
    al_draw_bitmap(start_page, 0, 0, 0);
    //al_draw_text(Large_font, WHITE, 270, 400, 0, "press S to start");
    al_flip_display();
}

void
GameWindow::draw_win_map()
{
    al_play_sample_instance(winSound);
    al_draw_bitmap(win_page, 0, 0, 0);
    char buffer[50];
    sprintf(buffer, "Time: %d   Score: %d", menu->getTime(), menu->getScore());
    al_draw_text(Large_font, WHITE, 600, 530, ALLEGRO_ALIGN_CENTER, buffer);
    al_flip_display();
}

void
GameWindow::draw_lose_map()
{
    al_stop_sample_instance(backgroundSound);
    al_play_sample_instance(loseSound);
    al_draw_bitmap(lose_page, 0, 0, 0);
    al_flip_display();
}

bool random(int x)
{
    static int seed = 0;
    seed%=1000;
    if(ran[seed++]%x)
    {
        return false;
    }
    return true;
}

