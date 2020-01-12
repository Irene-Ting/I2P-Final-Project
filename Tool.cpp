#include "Tool.h"

Tool::Tool(int pos_x = 0, int pos_y = 0) {}

Tool::~Tool()
{
    al_destroy_bitmap(img);
    al_destroy_sample(sample);
    al_destroy_sample_instance(toolSound);
}

void
Tool::Draw() {}

void
Tool::SelectedTool(int mouse_x, int mouse_y, int type)
{
    int draw_x = mouse_x - (ToolWidth[type]/2);
    int draw_y = mouse_y - (ToolHeight[type] - (ToolWidth[type]/2));
    char filename[50];
    ALLEGRO_BITMAP *bitmap;

    sprintf(filename, "./Tool/%s.png", ToolClass[type]);
    bitmap = al_load_bitmap(filename);

    al_draw_bitmap(bitmap, draw_x, draw_y, 0);
    al_destroy_bitmap(bitmap);
}
