#include "Player.h"
#include "GameWindow.h"

const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

Player::Player()
{
    cur_x = 2*grid_width;
    cur_y = 0*grid_height+ground;
    sample = al_load_sample("./Music/bottle_pop_2.wav");
    walkSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(walkSound, ALLEGRO_PLAYMODE_ONCE);

    sample = al_load_sample("./Music/bang_1.wav");
    softSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(softSound, ALLEGRO_PLAYMODE_ONCE);

    sample = al_load_sample("./Music/coin_3.wav");
    coinSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(coinSound, ALLEGRO_PLAYMODE_ONCE);

    sample = al_load_sample("./Music/cling_1.wav");
    energySound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(energySound, ALLEGRO_PLAYMODE_ONCE);

    sample = al_load_sample("./Music/sound6.wav");
    hitSound = al_create_sample_instance(sample);
    al_set_sample_instance_playmode(hitSound, ALLEGRO_PLAYMODE_ONCE);
}
Player::~Player()
{
    al_destroy_sample_instance(walkSound);
    al_destroy_sample_instance(softSound);
    al_destroy_sample_instance(coinSound);
    al_destroy_sample_instance(energySound);
}

void
Player::Draw()
{
    //ALLEGRO_BITMAP *playerImg;
    //playerImg = al_load_bitmap("./Material/Player1.png");
    //int draw_x
    //int draw_y
    al_draw_bitmap(img, cur_x, cur_y, 0);
}

bool
Player::Load_Move(Node* levelMap, Menu* menu, int d)
{
    int next_x, next_y;
    next_x = cur_x+axis_x[d]*step;
    next_y = cur_y+axis_y[d]*step;



    //printf("%d %d ", next_x, next_y);
    //printf("%d %d ", next_x/grid_width, next_y/grid_height);
    //printf("%d\n", levelMap[(next_x/grid_width)*15+(next_y/grid_height)].pathPoint);
    //menu->Change_Energy(-1);
    if(next_x<0 || next_x>field_width || next_y<ground || next_y>ground+field_height)
    {
        al_attach_sample_instance_to_mixer(hitSound, al_get_default_mixer());
        al_stop_sample_instance(hitSound);
        al_play_sample_instance(hitSound);
        return false;
    }
    else if(levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].type==HARD)
    {
        al_attach_sample_instance_to_mixer(hitSound, al_get_default_mixer());
        al_stop_sample_instance(hitSound);
        al_play_sample_instance(hitSound);
        return false;
    }
    else if(levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].type==PATH)
    {
        al_attach_sample_instance_to_mixer(walkSound, al_get_default_mixer());
        al_stop_sample_instance(walkSound);
        al_play_sample_instance(walkSound);
        cur_x = next_x;
        cur_y = next_y;
    }
    else if(levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].type==SOFT)
    {
        al_attach_sample_instance_to_mixer(softSound, al_get_default_mixer());
        al_stop_sample_instance(softSound);
        al_play_sample_instance(softSound);
        cur_x = next_x;
        cur_y = next_y;
        //BurrowGame->menu->Change_Energy(-1);
        menu->Change_Energy(-1);
        //levelMap[(next_x/grid_width)+(next_y/grid_height)*15].softPoint = false;
        levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].type = PATH;
    }

    if(levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].func==COIN)
    {
        al_attach_sample_instance_to_mixer(coinSound, al_get_default_mixer());
        al_stop_sample_instance(coinSound);
        al_play_sample_instance(coinSound);
        menu->Change_Coin(5);
        //levelMap[(next_x/grid_width)+(next_y/grid_height)*15].softPoint = false;
        levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].func = NORMAL;
    }
    else if(levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].func==ENERGY)
    {
        al_attach_sample_instance_to_mixer(energySound, al_get_default_mixer());
        al_stop_sample_instance(energySound);
        al_play_sample_instance(energySound);
        menu->Change_Energy(5);
        levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].func = NORMAL;
    }
    //destination
    if(cur_x == 22*grid_width && cur_y == ground) return true;
    return false;
}

