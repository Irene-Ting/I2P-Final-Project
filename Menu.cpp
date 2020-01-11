#include "Menu.h"
#include "Slider.h"
#include "Level.h"

const int ThumbWidth = 50;
const int ThumbHeight = 50;
const int gapX = 40, gapY = 36;
const int offsetX = 10 + field_width, offsetY = 150;
const int Initial_Energy = 500;
const int Initial_Coin = 100;
const int Initial_Time = 0;
const int Initial_Score = 0;

bool
Menu::isInRange(int point, int startPos, int length)
{
    if(point >= startPos && point <= startPos + length)
        return true;

    return false;
}

bool
Menu::Enough_Coin(int type)
{

    if(type < 0 || type >= Num_TowerType)
        return false;

    return (Coin + need_coin[type] >= 0);
}

Menu::Menu()
{
    char filename[50];

    EnergyPoint = 0;
    Coin = 0;
    Time = 0;

    for(int i=0;i<Num_TowerType; i++)
    {
        ALLEGRO_BITMAP *tower;
        //sprintf(filename, "./Tower/%s_Menu.png", TowerClass[i]);
        sprintf(filename, "./Tower/%s_menu.png", TowerClass[i]);
        tower = al_load_bitmap(filename);
        menu_tower.push_back(tower);
    }
    //char buffer[50];
    /*sprintf(buffer, "./Material/energy1.png", level->getlevel());
    energy = al_load_bitmap("./Material/energy1.png");
    coin = al_load_bitmap(buffer);*/
    //menuFont = al_load_ttf_font("pirulen.ttf", 20, 0); // load font
    stopIcon = al_load_bitmap("./Material/stop_40.png");
    pauseIcon = al_load_bitmap("./Material/pause_40.png");
    resumeIcon = al_load_bitmap("./Material/resume_40.png");
    menuFont = al_load_ttf_font("Caviar_Dreams_Bold.ttf", 18, 0);
    introFont = al_load_ttf_font("Caviar_Dreams_Bold.ttf", 14, 0);
}

Menu::~Menu()
{
    al_destroy_bitmap(energy);
    al_destroy_font(menuFont);

    for(int i=0; i < Num_TowerType; i++)
        al_destroy_bitmap(menu_tower[i]);

    menu_tower.clear();
}

void
Menu::Reset()
{
    EnergyPoint = Initial_Energy;
    Coin = Initial_Coin;
    Time = Initial_Time;
    score = Initial_Score;
    //killedMonster = 0;
}

void
Menu::Draw()
{
    char buffer[50];

    sprintf(buffer, "Level: %d", level);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 6, 0, buffer);

    sprintf(buffer, "Energy: %d", EnergyPoint);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 6+gapY, 0, buffer);

    sprintf(buffer, "Coin: %d", Coin);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 6 + 2*gapY, 0, buffer);

    sprintf(buffer, "Time: %d", Time);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX+100, 6, 0, buffer);

    sprintf(buffer, "Score: %d", score);
    al_draw_text(menuFont, al_map_rgb(255, 255, 255), offsetX, 6 + 3*gapY, 0, buffer);

    char intro[5][25] = {"Digging(Vertical)", "Digging(Horizontal)", "Bomb(3*3)",
    "Bomb(All)", "Dokodemo Door"};

    for(int i=0; i < Num_TowerType; i++)
    {
        int pos_x = offsetX;
        int pos_y = offsetY + (ThumbHeight + 8) * i;
        al_draw_filled_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 255, 255));
        //al_draw_bitmap(menu_tower[i], pos_x, pos_y, 0);
        al_draw_text(introFont, al_map_rgb(255, 255, 255), pos_x+56, pos_y+15, 0, intro[i]);
        if(!Enough_Coin(i))
        {
            al_draw_bitmap(menu_tower[i], pos_x, pos_y, 0);
            al_draw_filled_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgba(100, 100, 100, 100));
        }
        else if(i == selectedTower)
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 0, 0), 0);
        else
        {
            al_draw_bitmap(menu_tower[i], pos_x, pos_y, 0);
            al_draw_rectangle(pos_x, pos_y, pos_x + ThumbWidth, pos_y + ThumbHeight, al_map_rgb(255, 255, 255), 0);
        }
    }
    al_draw_bitmap(pauseIcon, field_width+8, 440, 0);
    al_draw_bitmap(stopIcon, field_width+54, 440, 0);
}

int
Menu::MouseIn(int mouse_x, int mouse_y)
{
    //bool enoughCoin;

    selectedTower = -1;
    if(mouse_x>0 && mouse_x<field_width && mouse_y>0 && mouse_y<field_height)
        return -1;
    for(int i=0; i < Num_TowerType; i++)
    {
        int pos_x = offsetX;
        int pos_y = offsetY + (ThumbHeight + 8) * i;

        if(isInRange(mouse_x, pos_x, ThumbWidth) && isInRange(mouse_y, pos_y, ThumbHeight))
        {
            if(Enough_Coin(i))
            {
                selectedTower = i;
                break;
            }
        }
    }
    return selectedTower;
}

/*bool
Menu::Subtract_HP(int escapeNum)
{
    HealthPoint -= escapeNum;

    return (HealthPoint == 0);
}*/

/*void
Menu::Gain_Score(int scoreWorth)
{
    killedMonster++;
    Score += scoreWorth;
}*/


