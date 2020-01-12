#include "Tower.h"

Tower::Tower(int pos_x = 0, int pos_y = 0) {}

Tower::~Tower()
{
    al_destroy_bitmap(img);
}

void
Tower::Draw() {}

void
Tower::SelectedTower(int mouse_x, int mouse_y, int type)
{
    int draw_x = mouse_x - (TowerWidth[type]/2);
    int draw_y = mouse_y - (TowerHeight[type] - (TowerWidth[type]/2));
    char filename[50];
    ALLEGRO_BITMAP *bitmap;

    sprintf(filename, "./Tower/%s.png", TowerClass[type]);
    bitmap = al_load_bitmap(filename);

    al_draw_bitmap(bitmap, draw_x, draw_y, 0);
    al_destroy_bitmap(bitmap);
}
