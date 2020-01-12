#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>

#define font_size 12
#define grid_width 40
#define grid_height 40
#define ground 120

#define window_width 1200
#define window_height 600
#define field_width 1000
#define field_height 480

#define NumOfToolType 5
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)

extern int ToolRadius[];
extern char ToolClass[][20];
extern int ToolWidth[];
extern int ToolHeight[];
extern char PlayerClass[][20];

enum {SHOVEL = 0, SPADE, BOMB, EXPLOSIVE, DOKODEMO};
enum {TSING = 1, HUA, NULL_};
#endif // GLOBAL_H_INCLUDED
