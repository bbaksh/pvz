#include "gameboard.h"

GameBoard::GameBoard()
{
}

QString GameBoard::setMainScreen()
{
    QString startScreen = "C:\\Qt\\Qt5.3.1\\Tools\\QtCreator\\bin\\pvz_bbaksh\\files\\startingscreen.png";
    currentScreen= new QPixmap(startScreen);
}

QPixmap GameBoard::getCurrentScreen()
{
    return *currentScreen;
}
