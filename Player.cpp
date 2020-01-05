#include "Player.h"
#include "GameWindow.h"

const int axis_x[] = {-1, 1, 0, 0};
const int axis_y[] = {0, 0, -1, 1};
const char direction_name[][10] = {"LEFT", "RIGHT", "UP", "DOWN"};

Player::Player()
{
    cur_x = 2*grid_width;
    cur_y = 0*grid_height;
}
Player::~Player(){}

void
Player::Draw()
{
    ALLEGRO_BITMAP *playerImg;
    playerImg = al_load_bitmap("./Material/Player1.png");
    al_draw_bitmap(playerImg, cur_x, cur_y, 0);
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
    if(levelMap[(next_x/grid_width)+(next_y/grid_height)*15].type==PATH)
    {
        cur_x = next_x;
        cur_y = next_y;
    }
    else if(levelMap[(next_x/grid_width)+(next_y/grid_height)*15].type==SOFT)
    {
        cur_x = next_x;
        cur_y = next_y;
        //BurrowGame->menu->Change_Energy(-1);
        menu->Change_Energy(-1);
        //levelMap[(next_x/grid_width)+(next_y/grid_height)*15].softPoint = false;
        levelMap[(next_x/grid_width)+(next_y/grid_height)*15].type = PATH;
    }

    if(levelMap[(next_x/grid_width)+(next_y/grid_height)*15].func==COIN)
    {
        menu->Change_Coin(5);
        printf("coin\n");
        //levelMap[(next_x/grid_width)+(next_y/grid_height)*15].softPoint = false;
        levelMap[(next_x/grid_width)+(next_y/grid_height)*15].func = NORMAL;
    }
    else if(levelMap[(next_x/grid_width)+(next_y/grid_height)*15].func==ENERGY)
    {
        menu->Change_Energy(5);
        levelMap[(next_x/grid_width)+(next_y/grid_height)*15].func = NORMAL;
        printf("energy\n");
    }
    if(cur_x == 480&&cur_y == 0) return true;
    return false;
}

