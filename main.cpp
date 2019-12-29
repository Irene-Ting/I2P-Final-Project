#include "GameWindow.h"
int main(int argc, char *argv[])
{

    GameWindow *BurrowGame= new GameWindow();
    BurrowGame->game_play();
    delete BurrowGame;

    return 0;
}
