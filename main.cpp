#include "GameWindow.h"

int main()
{

    GameWindow *BurrowGame = new GameWindow();
    BurrowGame->game_play();
    delete BurrowGame;

    return 0;
}
