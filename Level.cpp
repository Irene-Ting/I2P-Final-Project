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

    for(int i=0; i < NumOfGrid; i++)
    {
        int buf;
        fscanf(file, "%s", buffer);
        buf = atoi(buffer);
        this->levelMap[i].type = buf;
    }
    fclose(file);
}
