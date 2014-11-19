#include "gameboard.h"

GameBoard::GameBoard()
{
}

QString GameBoard::getMainScreen()
{
    QString mainscreen(homePath.currentPath()+"/mainscreen1.png");
    return mainscreen;
}

