#include "Game.h"

int main()
{
    Game* MainGame = I(Game);
    MainGame->Init();
    MainGame->Run();

    return 0;
}