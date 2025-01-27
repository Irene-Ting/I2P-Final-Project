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
    al_destroy_sample(sample);
    al_destroy_sample_instance(walkSound);
    al_destroy_sample_instance(softSound);
    al_destroy_sample_instance(coinSound);
    al_destroy_sample_instance(energySound);
    al_destroy_sample_instance(hitSound);
}

void
Player::Draw()
{
    al_draw_bitmap(img, cur_x, cur_y, 0);
    //al_flip_display();
}

bool
Player::Load_Move(Node* levelMap, Menu* menu, int d)
{
    int next_x, next_y;
    next_x = cur_x+axis_x[d]*step;
    next_y = cur_y+axis_y[d]*step;
    if(next_x<0 || next_x>=field_width || next_y<ground || next_y>=ground+field_height)
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
        menu->Change_Energy(-1);
        levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].type = PATH;
    }

    if(levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].func==COIN)
    {
        al_attach_sample_instance_to_mixer(coinSound, al_get_default_mixer());
        al_stop_sample_instance(coinSound);
        al_play_sample_instance(coinSound);
        menu->Change_Coin(5);
        levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].func = NORMAL;
    }
    else if(levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].func==ENERGY)
    {
        al_attach_sample_instance_to_mixer(energySound, al_get_default_mixer());
        al_stop_sample_instance(energySound);
        al_play_sample_instance(energySound);
        menu->Change_Energy(2);
        levelMap[(next_x/grid_width)+((next_y-ground)/grid_height)*field_width/40].func = NORMAL;
    }
    //destination
    if(cur_x == 22*grid_width && cur_y == ground)
    {
        return true;
    }
    return false;
}

void
Player::adjustVolume(double d)
{
    al_set_sample_instance_gain(walkSound, d);
    al_set_sample_instance_gain(softSound, d);
    al_set_sample_instance_gain(coinSound, d);
    al_set_sample_instance_gain(energySound, d);
    al_set_sample_instance_gain(hitSound, d);
}

bool
Player::goHere(Node* levelMap, Menu* menu, int x, int y)
{
    cur_x = x*grid_width;
    cur_y = y*grid_height;

    if(levelMap[(cur_x/grid_width)+((cur_y-ground)/grid_height)*field_width/40].func==COIN)
    {
        al_attach_sample_instance_to_mixer(coinSound, al_get_default_mixer());
        al_stop_sample_instance(coinSound);
        al_play_sample_instance(coinSound);
        menu->Change_Coin(5);
        levelMap[(cur_x/grid_width)+((cur_y-ground)/grid_height)*field_width/40].func = NORMAL;
    }
    else if(levelMap[(cur_x/grid_width)+((cur_y-ground)/grid_height)*field_width/40].func==ENERGY)
    {
        al_attach_sample_instance_to_mixer(energySound, al_get_default_mixer());
        al_stop_sample_instance(energySound);
        al_play_sample_instance(energySound);
        menu->Change_Energy(5);
        levelMap[(cur_x/grid_width)+((cur_y-ground)/grid_height)*field_width/40].func = NORMAL;
    }
    if(cur_x == 22*grid_width && cur_y == ground)
    {
        return true;
    }
    return false;
}

