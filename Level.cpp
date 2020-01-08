#include "Level.h"

LEVEL::LEVEL(const int level) {
    char buffer[50];
    setLevel(level);
}

LEVEL::~LEVEL()
{
    for(int i=0;i < NumOfGrid;i++)
    {
        levelMap[i].type = -1;
        levelMap[i].func = -1;
    }
}

void
LEVEL::setLevel(const int level)
{
    char buffer[50];
    FILE *file;

    sprintf(buffer, "LEVEL%d.txt", level);
    file = fopen(buffer, "r");
;
    this->level = level;
    //this->road_grid.clear();

    /*for(int i = 0; i < NumOfGrid; i++)
    {
        this->levelMap[i].pathPoint = false;
        this->levelMap[i].hardPoint = false;
        this->levelMap[i].softPoint = false;
    }*/

    /*fscanf(file, "%s", buffer);
    Monster_MAX = atoi(buffer);*/

    for(int i=0; i < NumOfGrid; i++)
    {
        //puts("buf = 0")
        int buf;
        fscanf(file, "%s", buffer);
        buf = atoi(buffer);
        this->levelMap[i].type = buf;
        /*if(buf==0) this->levelMap[i].pathPoint = true;
        else if(buf==1) this->levelMap[i].softPoint = true;
        else if(buf==2) this->levelMap[i].hardPoint = true;*/
    }

    /*while(fscanf(file, "%s", buffer) != EOF) {
        this->levelMap[atoi(buffer)].roadPoint = true;
        road_grid.push_back(atoi(buffer));
    }*/

    fclose(file);
}
