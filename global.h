#ifndef GLOBAL_H_INCLUDED
#define GLOBAL_H_INCLUDED

#include <allegro5/allegro_font.h>

#define font_size 12
#define grid_width 40
#define grid_height 40
#define ground 80

/*#define window_width 800
#define window_height 600
#define field_width 600
#define field_height 600*/

#define window_width 1200
#define window_height 600
#define field_width 1000
#define field_height 520

#define Num_TowerType 6
#define Num_MonsterType 4
#define NumOfGrid (field_width / grid_width) * (field_height / grid_height)

extern int TowerRadius[];
extern char TowerClass[][20];
extern int TowerWidth[];
extern int TowerHeight[];

enum {ARCANE = 0, ARCHER, CANON, POISON, STORM, NTOWER};
//enum {WOLF = 0, WOLFKNIGHT, DEMONNIJIA, CAVEMAN};
enum {PLAYER1 = 1, HuaHua, NUNU};
#endif // GLOBAL_H_INCLUDED
