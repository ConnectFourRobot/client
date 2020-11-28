#include "../../include/player/DebugPlayer.hpp"
#include "../../include/game/GameSettings.hpp"
#include <iostream>

int DebugPlayer::getMove(GameSettings & game)
{
    int column = 0, i;
    //add column numbers under grid
    std::cout << "-";
    for (i = 1; i < game.sizeX; i++)
    {
        std::cout << "--";
    }
    std::cout << std::endl;
    for (i = 0; i < game.sizeX; i++)
    {
        std::cout << (i+1) << " ";
    }
    std::cout << std::endl;

    std::cout << "Enter column 1 - " << game.sizeX << " or 0 for exit: ";
    std::cin >> column;
    if (column == 0)
    {
        std::cout << "Abort selected. Terminate programm" << std::endl;
        exit(0);
    }
    return column - 1;
}
