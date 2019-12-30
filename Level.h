#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include "global.h"

enum {PATH = 0, SOFT, HARD, ENERGY, COIN} ;

typedef struct Node {
    int h, g, f;
    int type;
    /*bool pathPoint;
    bool hardPoint;
    bool softPoint;
    bool energy;
    bool coin;*/
}Node;

class LEVEL {
public:
    LEVEL(const int);
    ~LEVEL();

    void setLevel(const int);
    bool isRoad(int index) { return levelMap[index].type==PATH; }
    int getMonsterSpeed() { return MonsterSpeed; }
    int getLevel() { return level; }
    //void search_destination();
    std::vector<int> ReturnPath() { return road_grid; }

    int MonsterNum[Num_MonsterType];
    Node levelMap[NumOfGrid];
private:

    std::vector<int> road_grid;
    // current level number
    int level = 1;
    // maximum number of monster of a level
    int Monster_MAX = 50;
    // frequency of producing  monster
    int MonsterSpeed = 80;
};


#endif // LEVEL_H_INCLUDED
