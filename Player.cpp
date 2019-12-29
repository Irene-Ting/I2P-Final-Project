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
    ALLEGRO_BITMAP *charaImg;
    charaImg = al_load_bitmap("./Material/Player1.png");
    al_draw_bitmap(charaImg, cur_x, cur_y, 0);
}

void
Player::Load_Move(Node* levelMap, int d)
{
    int next_x, next_y;
    next_x = cur_x+axis_x[d]*step;
    next_y = cur_y+axis_y[d]*step;
    printf("%d %d ", next_x, next_y);
    printf("%d\n", levelMap[(next_x/grid_width)*15+(next_y/grid_height)].pathPoint);
    if(levelMap[(next_x/grid_width)*15+(next_y/grid_height)].pathPoint)
    {
        cur_x = next_x;
        cur_y = next_y;
    }

}

