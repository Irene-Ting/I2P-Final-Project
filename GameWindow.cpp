#include "GameWindow.h"
#include "global.h"
#include <iostream>

#define WHITE al_map_rgb(255, 255, 255)
#define BLACK al_map_rgb(0, 0, 0)
#define ORANGE_LIGHT al_map_rgb(255, 196, 87)
#define ORANGE_DARK al_map_rgb(255, 142, 71)
#define PURPLE al_map_rgb(149, 128, 255)
#define BLUE al_map_rgb(77, 129, 179)

#define min(a, b) ((a) < (b)? (a) : (b))
#define max(a, b) ((a) > (b)? (a) : (b))
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

float Attack::volume = 1.0;

bool random(int);
int ran[NumOfGrid+5];
void set_attack_volume(float volume)
{
    Attack::volume = volume;
}

bool compare(Tower *t1, Tower *t2)
{
    return (t1->getY() <= t2->getY());
}

void
GameWindow::game_init()
{
    char buffer[50];

    icon = al_load_bitmap("./icon.png");
    background = al_load_bitmap("./StartBackground.jpg");
    start_page = al_load_bitmap("./Material/coollogo_com-435068.png");
    path = al_load_bitmap("./Material/path1.png");
    softImg = al_load_bitmap("./Material/soft1.png");
    hardImg = al_load_bitmap("./Material/hard1.png");
    coinImg = al_load_bitmap("./Material/player1.png");
    energyImg = al_load_bitmap("./Material/energy1.png");

    for(int i = 0; i < Num_TowerType; i++)
    {
        sprintf(buffer, "./Tower/%s.png", TowerClass[i]);
        tower[i] = al_load_bitmap(buffer);
    }

    al_set_display_icon(display, icon);
    al_reserve_samples(3);

    sample = al_load_sample("growl.wav");
    startSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(startSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(startSound, al_get_default_mixer());

    sample = al_load_sample("BackgroundMusic.ogg");
    backgroundSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(backgroundSound, ALLEGRO_PLAYMODE_ONCE);
    al_attach_sample_instance_to_mixer(backgroundSound, al_get_default_mixer());

    level = new LEVEL(1);
    menu = new Menu();
    slider = new Slider(790, 450);
    slider->set_label_content("Volume");
    player = new Player1();
}

bool
GameWindow::mouse_hover(int startx, int starty, int width, int height)
{
    if(mouse_x >= startx && mouse_x <= startx + width)
        if(mouse_y >= starty && mouse_y <= starty + height)
            return true;

    return false;
    //return true;
}

bool
GameWindow::isOnRoad()
{
    /*if(mouse_x-20 > 0 && mouse_x+20 < 600 && mouse_y-20 > 0 && mouse_y+20 < 600)
        return false;
    return true;*/
    return false;
    /*int startx, starty;
    int widthOfTower;

    widthOfTower = TowerWidth[selectedTower];

    for(int i=0; i < NumOfGrid; i++)
    {
        startx = (i % 15) * 40;
        starty = (i / 15) * 40;

        if(level->isRoad(i)) {
            if((mouse_x + (widthOfTower/2) < startx) || (mouse_x - (widthOfTower/2) > startx + grid_width))
                continue;
            else if((mouse_y + (widthOfTower/2) < starty) || (mouse_y > starty + grid_height))
                continue;
            else
                return true;
        }
    }
    return false;*/
}

Tower*
GameWindow::create_tower(int type)
{
    Tower *t = NULL;

    /*if(isOnRoad())
        return t;*/

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
    case NTOWER:
        t = new Ntower(mouse_x, mouse_y);
        break;
    default:
        break;
    }

    menu->Change_Coin(menu->getTowerCoin(type));

    return t;
}

/*Monster*
GameWindow::create_monster()
{
    Monster *m = NULL;

    if(level->MonsterNum[WOLF])
    {
        level->MonsterNum[WOLF]--;
        m = new Wolf(level->ReturnPath());
    }
    else if(level->MonsterNum[WOLFKNIGHT])
    {
        level->MonsterNum[WOLFKNIGHT]--;
        m = new WolfKnight(level->ReturnPath());
    }
    else if(level->MonsterNum[DEMONNIJIA])
    {
        level->MonsterNum[DEMONNIJIA]--;
        m = new DemonNijia(level->ReturnPath());
    }
    else if(level->MonsterNum[CAVEMAN])
    {
        level->MonsterNum[CAVEMAN]--;
        m = new CaveMan(level->ReturnPath());
    }
    else
    {
        al_stop_timer(monster_pro);
    }

    return m;
}*/

void
GameWindow::game_play()
{
    int msg;

    srand(time(NULL));

    msg = -1;
    game_reset();
    game_begin();
    //printf("&");
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

    timer = al_create_timer(1.0 / FPS);
    /*monster_pro = al_create_timer(1.0 / FPS);*/

    /*if(timer == NULL || monster_pro == NULL)
        show_err_msg(-1);*/

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

    font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",12,0); // load small font
    Medium_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",24,0); //load medium font
    Large_font = al_load_ttf_font("Caviar_Dreams_Bold.ttf",36,0); //load large font

    al_register_event_source(event_queue, al_get_display_event_source(display));
    al_register_event_source(event_queue, al_get_keyboard_event_source());
    al_register_event_source(event_queue, al_get_mouse_event_source());

    al_register_event_source(event_queue, al_get_timer_event_source(timer));
    //al_register_event_source(event_queue, al_get_timer_event_source(monster_pro));

    game_init();
}

void
GameWindow::game_begin()
{
    printf(">>> Start Level[%d]\n", level->getLevel());
    //draw_running_map();
    draw_start_map();

    al_play_sample_instance(startSound);
    srand(time(NULL));
    for(int i = 0; i<NumOfGrid; ++i) ran[i] = rand()%100;
    //for(int i = 0; i<NumOfGrid; ++i) printf("%d ", ran[i]);
    for(int i = 0; i<NumOfGrid; ++i)
    {
        level->levelMap[i].func = NORMAL;
        if(level->levelMap[i].type==PATH)
        {
            if(random(5))
                level->levelMap[i].func = ENERGY;
        }
        else if(level->levelMap[i].type==SOFT)
        {
            if(random(10)) level->levelMap[i].func = COIN;
        }
        else if(level->levelMap[i].type==HARD)
        {
            if(random(8)) level->levelMap[i].func = COIN;
        }

    }
    //while(al_get_sample_instance_playing(startSound));
    //al_play_sample_instance(backgroundSound);

    //al_start_timer(timer);
    //al_start_timer(monster_pro);

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
    unsigned int i, j;
    std::list<Tower*>::iterator it;

    /*DONE:*/
    /*Allow towers to detect if monster enters its range*/
    /*Hint: Tower::DetectAttack*/
    /*for(it = towerSet.begin(); it != towerSet.end(); it++)
    {
        for(i=0; i < monsterSet.size(); i++)
        {
            (*it)->DetectAttack(monsterSet[i]);
        }
    }*/

    // update every monster
    // check if it is destroyed or reaches end point
    /*for(i=0; i < monsterSet.size(); i++)
    {
        bool isDestroyed = false, isReachEnd = false;

        /*DONE:*/
        /*1. For each tower, traverse its attack set*/
        /*2. If the monster collide with any attack, reduce the HP of the monster*/
        /*3. Remember to set isDestroyed to "true" if monster is killed*/
        /*Hint: Tower::TriggerAttack*/
        /*for(it = towerSet.begin(); it != towerSet.end(); it++)
        {
            if((*it)->TriggerAttack(monsterSet[i]))
                isDestroyed = true;
        }

        isReachEnd = monsterSet[i]->Move();

        if(isDestroyed)
        {
            Monster *m = monsterSet[i];

            menu->Change_Coin(m->getWorth());
            menu->Gain_Score(m->getScore());
            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;

        }
        else if(isReachEnd)
        {
            Monster *m = monsterSet[i];

            if(menu->Subtract_HP())
                return GAME_EXIT;

            monsterSet.erase(monsterSet.begin() + i);
            i--;
            delete m;
        }
    }*/

    /*DONE:*/
    /*1. Update the attack set of each tower*/
    /*Hint: Tower::UpdateAttack*/
    /*for(it = towerSet.begin(); it != towerSet.end(); it++)
    {
        (*it)->UpdateAttack();
    }*/

    return GAME_CONTINUE;
}

void
GameWindow::game_reset()
{
    // reset game and begin
    for(auto&& child : towerSet) {
        delete child;
    }
    towerSet.clear();
    //monsterSet.clear();


    selectedTower = -1;
    lastClicked = -1;
    Time_Inc_Count = 0;
    Energy_Inc_Count = 0;
    //Monster_Pro_Count = 0;
    mute = false;
    redraw = false;
    scene = ACTIVATE;
    menu->Reset();

    // stop sample instance
    al_stop_sample_instance(backgroundSound);
    al_stop_sample_instance(startSound);

    // stop timer
    al_stop_timer(timer);
    //al_stop_timer(monster_pro);
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

    al_destroy_timer(timer);
    //al_destroy_timer(monster_pro);

    for(int i=0;i<5; i++)
        al_destroy_bitmap(tower[i]);

    al_destroy_bitmap(icon);
    al_destroy_bitmap(background);

    al_destroy_sample(sample);
    al_destroy_sample_instance(startSound);
    al_destroy_sample_instance(backgroundSound);
    delete slider;
    delete level;
    delete menu;
}

int
GameWindow::process_event()
{
    int i;
    int instruction = GAME_CONTINUE;

    // offset for pause window
    int offsetX = field_width/2 - 200;
    int offsetY = field_height/2 - 200;

    bool win = false;

    al_wait_for_event(event_queue, &event);
    redraw = false;

    if(event.type == ALLEGRO_EVENT_TIMER) {
        if(event.timer.source == timer) {
            redraw = true;

            if(Time_Inc_Count==0)
                menu->Change_Time(1);
            Time_Inc_Count = (Time_Inc_Count + 1) % TimeSpeed;

            if(Energy_Inc_Count==0)
                menu->Change_Energy(-1);
            Energy_Inc_Count = (Energy_Inc_Count + 1) % EnergySpeed;

            if(menu->getEnergy()<0) scene = GAMELOSE;
            /*if(monsterSet.size() == 0 && !al_get_timer_started(monster_pro))
            {
                al_stop_timer(timer);
                return GAME_EXIT;
            }*/
        }
        /*else {
            if(Monster_Pro_Count == 0) {
                Monster *m = create_monster();

                if(m != NULL)
                    monsterSet.push_back(m);
            }
            Monster_Pro_Count = (Monster_Pro_Count + 1) % level->getMonsterSpeed();
        }*/
    }
    else if(event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
        return GAME_EXIT;
    }
    else
    {
        switch(scene)
        {
            case ACTIVATE:
                if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
                    switch(event.keyboard.keycode)
                    {
                        case ALLEGRO_KEY_S:
                            scene++;
                            al_start_timer(timer);
                            //al_start_timer(monster_pro);
                            al_play_sample_instance(backgroundSound);
                            break;
                    }
                }
                break;
            case GAMERUN:
                if(event.type == ALLEGRO_EVENT_KEY_DOWN) {
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

                        case ALLEGRO_KEY_P:
                            /*DONE: handle pause event here*/
                            if(al_get_timer_started(timer))
                            {
                                al_stop_timer(timer);
                                //al_stop_timer(monster_pro);
                            }
                            else
                            {
                                al_start_timer(timer);
                                //al_start_timer(monster_pro);
                            }
                            break;
                        case ALLEGRO_KEY_M:
                            mute = !mute;
                            if(mute)
                                al_stop_sample_instance(backgroundSound);
                            else
                                al_play_sample_instance(backgroundSound);
                            break;
                    }
                }
                else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_DOWN) {
                    if(event.mouse.button == 1) {
                        /*if(selectedTower != -1 && mouse_hover(0, 0, field_width, field_height)) {
                            Tower *t = create_tower(selectedTower);

                            if(t == NULL)
                                printf("Wrong place\n");
                            else {
                                towerSet.push_back(t);
                                towerSet.sort(compare);
                            }
                        } else*/ if(selectedTower == -1){
                            std::list<Tower*>::iterator it = towerSet.begin();
                            if(lastClicked != -1)
                            {
                                std::advance(it, lastClicked);
                                (*it)->ToggleClicked();
                            }
                            for(i=0, it = towerSet.begin(); it != towerSet.end(); it++, i++)
                            {
                                Square *square = (*it)->getSquare();
                                int t_width = (*it)->getWidth();

                                if(mouse_hover(square->x - t_width/2, square->y, t_width, t_width/2))
                                {
                                    (*it)->ToggleClicked();
                                    lastClicked = i;
                                    break;
                                } else {
                                    lastClicked = -1;
                                }
                            }

                        }
                        selectedTower = menu->MouseIn(mouse_x, mouse_y);
                        if(slider->isClicked(mouse_x, mouse_y))
                        {
                            slider->toggleDrag();
                        }
                    // check if user wants to create some kind of tower
                    // if so, show tower image attached to cursor
                    }
            }
            else if(event.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP) {
                if(selectedTower != -1 && mouse_hover(0, 0, field_width, field_height)) {
                    Tower *t = create_tower(selectedTower);
                    if(t == NULL)
                        printf("Wrong place\n");
                    else {
                        //vector<int> change;
                        std::vector<int> change;
                        towerSet.push_back(t);
                        towerSet.sort(compare);
                        selectedTower = -1;
                        change = t->Utilize(mouse_x, mouse_y);
                        for(auto i : change)
                            if(i>=0 && i<=NumOfGrid)
                                level->levelMap[i].type = PATH;

                    }
                }
                else if(slider->isDragged())
                {
                    slider->toggleDrag();
                }

            }
            else if(event.type == ALLEGRO_EVENT_MOUSE_AXES){
                mouse_x = event.mouse.x;
                mouse_y = event.mouse.y;
                menu->MouseIn(mouse_x, mouse_y);
                if(slider->isDragged())
                {
                    slider->Drag(mouse_x, mouse_y);
                    al_set_sample_instance_gain(backgroundSound, slider->getDegree());
                }
            }
                break;
            }
    }
    if(win) scene = GAMEWIN;
    if(redraw) {
        // update each object in game
        // Re-draw map
        if(scene==GAMERUN)
        {
            instruction = game_update();
            draw_running_map();
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

    al_clear_to_color(al_map_rgb(100, 100, 100));
    al_draw_bitmap(background, 0, 0, 0);

    for(i = 0; i < field_height/40; i++)
    {
        for(j = 0; j < field_width/40; j++)
        {
            char buffer[50];
            sprintf(buffer, "%d", i*field_width/40 + j);
            //printf("here\n");
            switch(level->levelMap[i*field_width/40 + j].type)
            {
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
            /*if(level->levelMap[i*15+j].pathPoint)
                al_draw_bitmap(path, j*40, i*40, 0);
            else if(level->levelMap[i*15+j].softPoint)
                al_draw_bitmap(softImg, j*40, i*40, 0);
            else if(level->levelMap[i*15+j].hardPoint)
                al_draw_bitmap(hardImg, j*40, i*40, 0);*/
            /*if(level->isRoad(i*15 + j)) {
                //al_draw_filled_rectangle(j*40, i*40, j*40+40, i*40+40, al_map_rgb(255, 244, 173));
                al_draw_bitmap(path, j*40, i*40, 0);

            }*/
            //al_draw_text(font, al_map_rgb(0, 0, 0), j*40, i*40, 0, buffer);
        }
    }
    //monsterSet[0]->Draw();
    /*for(i=0; i<monsterSet.size(); i++)
    {
        monsterSet[i]->Draw();
    }*/

    for(std::list<Tower*>::iterator it = towerSet.begin(); it != towerSet.end(); it++)
        (*it)->Draw();

    if(selectedTower != -1)
        Tower::SelectedTower(mouse_x, mouse_y, selectedTower);

    //al_draw_filled_rectangle(field_width, 0, window_width, window_height, al_map_rgb(100, 100, 100));

    menu->Draw();
    slider->Draw();
    player->Draw();
    al_flip_display();
}

void
GameWindow::draw_start_map()
{
    al_clear_to_color(BLACK);
    al_draw_bitmap(start_page, 230, 150, 0);
    al_draw_text(Large_font, WHITE, 270, 400, 0, "press S to start");
    al_flip_display();
}

void
GameWindow::draw_win_map()
{
    al_clear_to_color(BLACK);
    al_draw_bitmap(start_page, 230, 150, 0);
    al_draw_text(Large_font, WHITE, 270, 400, 0, "win");
    al_flip_display();
}

void
GameWindow::draw_lose_map()
{
    al_clear_to_color(BLACK);
    al_draw_bitmap(start_page, 230, 150, 0);
    al_draw_text(Large_font, WHITE, 270, 400, 0, "lose");
    al_flip_display();
}


bool random(int x)
{
    static int seed = 0;
    //srand(time(NULL)+seed++);
    //srand((int)time(0)+(seed++));
    if(ran[seed++]%x)
    {
        //printf("false\n");
        return false;
    }

    //printf("true\n");
    return true;
}

