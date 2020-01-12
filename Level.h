#ifndef LEVEL_H_INCLUDED
#define LEVEL_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>
#include <vector>
#include "global.h"

enum {PATH = 0, SOFT, HARD} ;
enum {NORMAL = 0, ENERGY, COIN};

typedef struct Node {
    int h, g, f;
    int type;
    int func;
}Node;

class LEVEL {
public:
    LEVEL(const int);
    ~LEVEL();

    void setLevel(const int);
    int getLevel() { return level; }
    Node levelMap[NumOfGrid];
private:
    int level = 1;
};

#endif // LEVEL_H_INCLUDED
